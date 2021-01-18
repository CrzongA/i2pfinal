#include "../include/scene_start.h"
#include "../include/scene_gameover.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "../include/game.h"
#include "../include/utility.h"
#include "../include/shared.h"
#include <math.h>

// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */

// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.

static ALLEGRO_BITMAP* img_background;
static ALLEGRO_BITMAP* img_crosshair;
static ALLEGRO_BITMAP* img_plane;
static ALLEGRO_BITMAP* img_enemy;
static ALLEGRO_BITMAP* img_pBullets;
static ALLEGRO_BITMAP* img_eBullets;
static ALLEGRO_BITMAP* img_laser;

typedef struct {
    const char* name;
    // The center coordinate of the image.
    float x, y;
    // The width and height of the object.
    float w, h;
    // The velocity in x, y axes.
    float vx, vy;
    // The rotation of the image in radians.
    double angle;
    // Timestamp of initialization of the object.
    double initT, vxRange;
    // Health and damage of object.
    float health, baseHealth, damage;
    // Should we draw this object on the screen.
    bool hidden;
    // The pointer to the object’s image.
    ALLEGRO_BITMAP* img;
} MovableObject;

typedef struct {
    int id, enemyCount, enemyBullets, maxscore;
    float enemySpeed, bulletSpeed, enemyHealth, enemyBulletDamage, enemyCrashDamage, playerBaseHealth, playerDamage, playerSpeed, scorecoef;
} Level;

static void init(void);
static void initEnemy(int, ALLEGRO_BITMAP*);
static void update(void);
static void draw_movable_object(MovableObject obj);
static void draw(void);
static void destroy(void);
static double enemy_move_sin(double xrange, double progress, double freq);
static void enemy_damaged(MovableObject* obj);
static void check_health();

#define MAX_ENEMY 10
#define MAX_BULLET 25
#define MAX_ENEMY_BULLET 5
#define MAX_LEVELS 5
#define MAX_GAMETIME 120
#define HUD_HINT_DURATION 1
static Level levels[MAX_LEVELS];
static MovableObject plane;
static MovableObject planeHealth;
static MovableObject enemies[MAX_ENEMY];
static MovableObject enemyHealth[MAX_ENEMY];
static MovableObject laser;
// [HACKATHON 2-3]
// TODO: Declare an array to store bullets with size of max bullet count.
// Uncomment and fill in the code below.
static MovableObject playerBullets[MAX_BULLET];
static MovableObject enemyBullets[MAX_ENEMY][MAX_ENEMY_BULLET];

// [HACKATHON 2-4]
// TODO: Set up bullet shooting cool-down variables.
// 1) Declare your shooting cool-down time as constant. (0.2f will be nice)
// 2) Declare your last shoot timestamp.
// Uncomment and fill in the code b//        enemies[i].vx = enemy_move_sin(enemies[i].initT, enemies[i].vxRange, enemies[i].y-80);
//        enemies[i].vy = 0.5;elow.
static const float MAX_COOLDOWN = 0.08;
static double game_start_timestamp;
static double prev_pause_timestamp;
static double prev_paused_time;
static double total_paused_time;
static double enemy_last_shoot_timestamp;
static double player_last_shoot_timestamp;
static double levelup_timestamp;
static double laser_charge=0; // 0 to 1
bool mouseleftdown, mouserightdown;
static int currentLevel;
int playerScore[2];
int gameMode; // 1 for singleplayer, 2 for multiplayer
int parallaxPxs=100;
bool bossmode;
bool paused;
#ifdef audio
static ALLEGRO_SAMPLE* bgm;
static ALLEGRO_SAMPLE_ID bgm_id;
#endif
static bool draw_gizmos;

static void init(void) {
    al_clear_to_color(al_map_rgb(0,0,0));
    int i;
    // Preload assets
    double rng = rand()/RAND_MAX;
    img_background = load_bitmap_resized(concat(img_path, startbgs[2]), SCREEN_W+parallaxPxs, SCREEN_H*4);
    img_plane = plane.img = load_bitmap_resized(concat(img_path, playerimg[playerShip]), player_W, player_H);
    img_pBullets = al_load_bitmap(concat(img_path, "bullet-red.png"));
    img_eBullets = al_load_bitmap(concat(img_path, "bullet-blue.png"));
    img_crosshair = al_load_bitmap(concat(img_path, "crosshair1.png"));
    img_laser = load_bitmap_resized(concat(img_path, "laser.png"), SCREEN_W, 50);
    enemy_last_shoot_timestamp = 0;
    // difficulty settings
    for (i=1; i<MAX_LEVELS; i++){
        levels[i].id = i;
        levels[i].enemyHealth = 80+20*i;
        levels[i].enemySpeed = i*0.8;
        levels[i].bulletSpeed = i/5*10 + 10;
        levels[i].enemyCrashDamage = 33*i;
        levels[i].enemyBulletDamage = 20 + 5*i;
        levels[i].enemyBullets = i*3;
        levels[i].playerBaseHealth = 100*i;
        levels[i].playerDamage = 20*i;
        levels[i].playerSpeed = 10 + 5*i;
        levels[i].enemyCount = 20 + i*10;
        levels[i].scorecoef = i;
        switch(i){
            default: case 1: levels[i].maxscore=100; break;
            case 2: levels[i].maxscore=300; break;
            case 3: levels[i].maxscore=500; break;
            case 4: levels[i].maxscore=800; break;
            case 5: levels[i].maxscore=1200; break;
        }
    }
    currentLevel=1;
    bossmode=false;
    paused=false;
    mouseleftdown = mouserightdown = false;
//    for (int i=0;i<=gameMode; i++)
    playerScore[0] = playerScore[1]=0;
    plane.name = "player";
    plane.x = (float)SCREEN_W/2;
    plane.y = (float)SCREEN_H*4/5;
    plane.w = player_W; //???
    plane.h = player_H; //???
    plane.baseHealth = plane.health = levels[currentLevel].playerBaseHealth;
    planeHealth.name = "healthbar";
    planeHealth.x = plane.x;
    planeHealth.y = plane.y-5;
    planeHealth.w = al_get_bitmap_width(img_plane);
    planeHealth.h = 1;
    planeHealth.baseHealth = planeHealth.health = plane.baseHealth;
    //enemy init
    img_enemy = load_bitmap(concat(img_path,enemyimg[0]));
    for (i = 0; i < MAX_ENEMY; i++) {
        initEnemy(i, img_enemy);
        game_log("[enemy %d] xVelCoef: %f", i, enemies[i].vxRange);
        for (int j=0; j<MAX_ENEMY_BULLET;j++){
            enemyBullets[i][j].name = "ebullet";
            enemyBullets[i][j].img = img_eBullets;
            enemyBullets[i][j].w = al_get_bitmap_width(img_eBullets);
            enemyBullets[i][j].h = al_get_bitmap_height(img_eBullets);
            enemyBullets[i][j].vx = 0;
            enemyBullets[i][j].vy = levels[currentLevel].bulletSpeed;
            enemyBullets[i][j].angle = 0;
            enemyBullets[i][j].hidden = true;
        }
    }

    for (i=0; i<MAX_BULLET; i++) {
        playerBullets[i].name = "pbullet";
        playerBullets[i].img = img_pBullets;
        playerBullets[i].w = al_get_bitmap_width(img_pBullets);
        playerBullets[i].h = al_get_bitmap_height(img_pBullets);
        playerBullets[i].vx = 0;
        playerBullets[i].vy = -levels[currentLevel].bulletSpeed;
        playerBullets[i].angle = 0;
        playerBullets[i].hidden = true;
    }

    laser.name = "laser";
    laser.angle=0;
    laser.h = 25;
    laser.w = SCREEN_W;
    laser.hidden = true;

    levelup_timestamp = total_paused_time = 0;
    game_start_timestamp = al_get_time();
//    game_log("start time %f", game_start_timestamp);

#ifdef audio
    // Can be moved to shared_init to decrease loading time.
    bgm = load_audio(concat(audio_path,"mythica.ogg"));
    game_log("Start scene initialized");
    bgm_id = play_bgm(bgm, 1);
#endif
}

static void initEnemy(int idx, ALLEGRO_BITMAP *image_enemy){
    enemies[idx].name = "enemy";
    enemies[idx].img = img_enemy;
    enemies[idx].w = al_get_bitmap_width(img_enemy);
    enemies[idx].h = al_get_bitmap_height(img_enemy);
    enemies[idx].initT = al_get_time();
    enemies[idx].vxRange = 10; //(rand() / (double)RAND_MAX) * 2 + 2
    enemies[idx].vx = 2;
    enemies[idx].vy = (rand()/(float)RAND_MAX) * 2 + levels[currentLevel].enemySpeed;
    enemies[idx].x = (rand()/(float)RAND_MAX)*SCREEN_W*4/6 + SCREEN_W/6;
    enemies[idx].y = 0-enemies[idx].h;
    enemies[idx].health = levels[currentLevel].enemyHealth;
    enemyHealth[idx].name = "healthbar";
    enemyHealth[idx].health = enemies[idx].health;
    enemyHealth[idx].baseHealth = enemies[idx].baseHealth = levels[currentLevel].enemyHealth;
    enemyHealth[idx].x = enemies[idx].x;
    enemyHealth[idx].y = enemies[idx].y-5;
    enemyHealth[idx].w = al_get_bitmap_width(img_enemy);
    enemyHealth[idx].h = 1;
}

static void update(void) {
    double now = al_get_time();
    if(key_state[ALLEGRO_KEY_ESCAPE]&& !paused) {
        paused = true;
        prev_pause_timestamp = al_get_time();
        prev_paused_time = total_paused_time;
    }
    if(paused){
        if (key_state[ALLEGRO_KEY_ENTER] || key_state[ALLEGRO_KEY_PAD_ENTER]) {
            paused = false;
            game_log("timestamp %f", al_get_time());
        }
        total_paused_time = now - prev_pause_timestamp + prev_paused_time;
    }
    else {
        if(bossmode){

        }

        if (mouserightdown){
            laser_charge += laser_charge>=1 ? 0 : 0.01;
            for (int i=0;i<MAX_ENEMY;i++){
                for (int j=0;j<MAX_ENEMY_BULLET;j++){
                    game_log("dydx %f laser %f", (plane.y-enemyBullets[i][j].y)/(plane.x-enemyBullets[i][j].x), tan(laser.angle));
                    if ((plane.y-enemyBullets[i][j].y)/(plane.x-enemyBullets[i][j].x) == tan(laser.angle)-90)
                        enemyBullets[i][j].hidden=true;
                    if((plane.y-enemies[i].y)/(plane.x-enemies[i].x) == tan(laser.angle)) {
                        initEnemy(i, enemies[i].img);
                    }
                }
            }
        }
        else{
            laser_charge -= laser_charge <=0 ? 0 : 0.08;
        }

        plane.vx = plane.vy = 0;
        if (key_state[ALLEGRO_KEY_UP] || key_state[ALLEGRO_KEY_W])
            plane.vy -= 1;
        if (key_state[ALLEGRO_KEY_DOWN] || key_state[ALLEGRO_KEY_S])
            plane.vy += 1;
        if (key_state[ALLEGRO_KEY_LEFT] || key_state[ALLEGRO_KEY_A])
            plane.vx -= 1;
        if (key_state[ALLEGRO_KEY_RIGHT] || key_state[ALLEGRO_KEY_D])
            plane.vx += 1;
        // 0.71 is (1/sqrt(2)).
        plane.y += plane.vy * levels[currentLevel].playerSpeed * (plane.vx ? 0.71f : 1);
        plane.x += plane.vx * levels[currentLevel].playerSpeed * (plane.vy ? 0.71f : 1);

        if (plane.x - plane.w / 2 < 0)
            plane.x = plane.w / 2;
        else if (plane.x + plane.w / 2 > SCREEN_W)
            plane.x = SCREEN_W - plane.w / 2;
        if (plane.y - plane.h / 2 < 0)
            plane.y = plane.h / 2;
        else if (plane.y + plane.h / 2 > SCREEN_H)
            plane.y = SCREEN_H - plane.h / 2;

        planeHealth.x = plane.x - plane.w / 2;
        planeHealth.y = plane.y - plane.h;


        int i;
        // handle shooting bullets
        double now = al_get_time();
        if (key_state[ALLEGRO_KEY_SPACE] && (now - player_last_shoot_timestamp >= MAX_COOLDOWN)) {
            for (i = 0; i < MAX_BULLET; i++) {
                if (playerBullets[i].hidden) {
                    playerBullets[i].vy = -levels[currentLevel].bulletSpeed;
                    playerBullets[i].vx = 0;
                    playerBullets[i].angle =0;
                    player_last_shoot_timestamp = now;
                    playerBullets[i].hidden = false;
                    playerBullets[i].x = plane.x;
                    playerBullets[i].y = plane.y;
                    break;
                }
            }
//            game_log("straight shooting");
        }
        else if (mouseleftdown && (now - player_last_shoot_timestamp >= MAX_COOLDOWN)){
            double angle = atan2(plane.y-mouse_y,plane.x-mouse_x );
            for (i=0; i<MAX_BULLET; i++){
                if(playerBullets[i].hidden){
                    player_last_shoot_timestamp = now;
                    playerBullets[i].vx = -levels[currentLevel].bulletSpeed * cos(angle);
                    playerBullets[i].vy = -levels[currentLevel].bulletSpeed * sin(angle);
                    playerBullets[i].angle = angle - ALLEGRO_PI/2;
                    playerBullets[i].hidden = false;
                    playerBullets[i].x = plane.x;
                    playerBullets[i].y = plane.y;
//            game_log("bullet %d angle %f", i, playerBullets[i].angle);
                    break;
                }
            }
//            game_log("directional shooting");
        }
        else if (mouserightdown && laser_charge>=1){
            double angle = atan2(plane.y-mouse_y,plane.x-mouse_x );
            laser.angle = angle - ALLEGRO_PI;
        }
        if (now-enemy_last_shoot_timestamp>=MAX_COOLDOWN){
            for (i=0;i<MAX_ENEMY;i++) {
                for (int j = 0; j < MAX_ENEMY_BULLET; j++) {
                    enemyBullets[i][j].vy = levels[currentLevel].bulletSpeed;
                    if (enemyBullets[i][j].hidden) {
                        enemy_last_shoot_timestamp = now;
                        enemyBullets[i][j].hidden = false;
                        enemyBullets[i][j].x = enemies[i].x;
                        enemyBullets[i][j].y = enemies[i].y;
                        break;
                    }
                }
            }
        }

        // bullet-bullet collision
        for (i=0;i<MAX_BULLET;i++) {
            for (int k=0;k<MAX_ENEMY;k++)
            for (int j = 0; j < MAX_ENEMY_BULLET; j++) {
                if (!enemyBullets[k][j].hidden &&
                    bx_in_bx(enemyBullets[k][j].x, enemyBullets[k][j].y, enemyBullets[k][j].w, enemyBullets[k][j].h, playerBullets[i].x,
                             playerBullets[i].y,
                             playerBullets[i].w, playerBullets[i].h)) {
                    enemyBullets[k][j].hidden = playerBullets[i].hidden = true;
                }
            }
        }

        // update bullet position
        for (i=0;i<MAX_BULLET;i++){
            if (!playerBullets[i].hidden) {
                playerBullets[i].y += playerBullets[i].vy;
                playerBullets[i].x += playerBullets[i].vx;
                if (playerBullets[i].y < 0
                    || playerBullets[i].y - playerBullets[i].h > SCREEN_H
                    || playerBullets[i].x < 0
                    || playerBullets[i].x - playerBullets[i].w > SCREEN_W)
                    playerBullets[i].hidden = true;
            }
        }
        for (i = 0; i < MAX_ENEMY; i++) {
            for (int j = 0; j < MAX_ENEMY_BULLET; j++) {
                if (!enemyBullets[i][j].hidden) {
                    enemyBullets[i][j].y += enemyBullets[i][j].vy;
                    if (enemyBullets[i][j].y < 0 || enemyBullets[i][j].h > SCREEN_H)
                        enemyBullets[i][j].hidden = true;
                }
            }
        }

        // update enemy-related parameters
        for (i = 0; i < MAX_ENEMY; i++) {
            // update enemy position
            if (!enemies[i].hidden) {
                enemies[i].x += enemy_move_sin(enemies[i].vxRange,
                                               fabs((enemies[i].y - (double) SCREEN_H)) / (double) SCREEN_H *
                                               ALLEGRO_PI * 2, enemies[i].vx);
                enemies[i].y += enemies[i].vy;
            }
            if (enemies[i].y > (SCREEN_H + enemies[i].h)) initEnemy(i, enemies[i].img);

            // bullet-enemy collision detection
            for (int j = 0; j < MAX_BULLET; j++) {
                if (!playerBullets[j].hidden &&
                    pnt_in_ellipse(playerBullets[j].x, playerBullets[j].y, enemies[i].x, enemies[i].y,
                             enemies[i].w, enemies[i].h)) {
                    playerBullets[j].hidden = true;
                    enemyHealth[i].health = enemies[i].health -= levels[currentLevel].playerDamage;
                    if (gameMode == 0) playerScore[0]+=levels[currentLevel].scorecoef*1;
                    //todo: explosion effect
//                for (int j=0;j<=gameMode;j++)
//                game_log("player score: %d", playerScore[j]);
                }
            }

            // bullet-player collision detection
            for (int j = 0; j < MAX_BULLET; j++) {
                if (!enemyBullets[i][j].hidden &&
                    pnt_in_ellipse(enemyBullets[i][j].x, enemyBullets[i][j].y, plane.x, plane.y,
                                   plane.w, plane.h)) {
                    enemyBullets[i][j].hidden = true;
                    planeHealth.health = plane.health -= levels[currentLevel].playerDamage;
//                    if (gameMode == 0) playerScore[0] += levels[currentLevel].scorecoef*1;
                }
            }

            //enemy-player collision detection
            if (pnt_in_ellipse(plane.x, plane.y, enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h) || pnt_in_ellipse(enemies[i].x, enemies[i].y, plane.x, plane.y, plane.w, plane.h)) {
                //todo: explosion effect
                initEnemy(i, enemies[i].img);
                planeHealth.health = plane.health -= levels[currentLevel].enemyCrashDamage;
                if (gameMode == 0) playerScore[0] += levels[currentLevel].scorecoef*5;

                game_log("player hit");
            }

            if (enemies[i].health < 0) {
                for (int j = 0; j <= gameMode; j++)
                    playerScore[j]++;
                initEnemy(i, enemies[i].img);
                game_log("enemy %d destroyed", i);
            }

            //update enemy healthbar
            enemyHealth[i].x = enemies[i].x - enemies[i].w / 2;
            enemyHealth[i].y = enemies[i].y - enemies[i].h / 2 - 5;
            enemyHealth[i].health = enemies[i].health;
        }
        // check if evolving to next level is possible
        if (gameMode == 0) {
            if (playerScore[0] >= levels[currentLevel].maxscore) {
                if (currentLevel == 5) {
                    bossmode = true;
                }
                currentLevel++;
                levelup_timestamp = now;
                planeHealth.baseHealth = planeHealth.health = plane.baseHealth = plane.health = levels[currentLevel].playerBaseHealth;
            }
        }
//    game_log("player health %f", plane.health);
        check_health();
    }
}

static double enemy_move_sin(double xrange, double progress, double freq) {
    return xrange * sin(progress * freq); //
}
// [HACKATHON 3-1]
// TODO: Declare 2 variables for storing settings images.
// Uncomment and fill in the code below.

static double boss_movement(double time){

}

static void enemy_damaged(MovableObject* obj){
    double start = al_get_time();
}

static void check_health(){
    if (plane.health<=0){
        game_change_scene(scene_gameover_create());
    }
}

static void draw_movable_object(MovableObject obj) {
    if (obj.hidden)
        return;
    if(obj.img) {// [HACKATHON 3-1]
// TODO: Declare 2 variables for storing settings images.
// Uncomment and fill in the code below.

        if (strcmp("pbullet", obj.name) == 0)
            al_draw_rotated_bitmap(obj.img, obj.w / 2, obj.h / 2, obj.x, obj.y, obj.angle, 0);
        else al_draw_bitmap(obj.img, round(obj.x - obj.w / 2), round(obj.y - obj.h / 2), 0);
    }
    // draw health bar
    else if (strcmp("healthbar", obj.name)==0) {
        al_draw_rectangle(obj.x, obj.y, round(obj.x + obj.w), round(obj.y + obj.h), al_map_rgb(255, 255, 255), 5);
        al_draw_rectangle(obj.x, obj.y, round(obj.x + (obj.w * obj.health / obj.baseHealth)), round(obj.y + obj.h),
                          al_map_rgb(255, 0, 0), 5);
    }
    // draw player bullet, consider rotation
    // debug movable objects
    if (draw_gizmos) {
        al_draw_rectangle(round(obj.x - obj.w / 2), round(obj.y - obj.h / 2),
            round(obj.x + obj.w / 2) + 1, round(obj.y + obj.h / 2) + 1, al_map_rgb(255, 0, 0), 0);
        al_draw_filled_circle(obj.x, obj.y, 5, al_map_rgb(255, 0, 0));
        // debug plane position
        al_draw_textf(font_pirulen_15, al_map_rgb(255, 0, 0), SCREEN_W*9/10.0, SCREEN_H*9/10.0, 0, "x:%f", plane.x);
        al_draw_textf(font_pirulen_15, al_map_rgb(255, 0, 0), SCREEN_W*9/10.0, SCREEN_H*9/10.0+15, 0, "y:%f", plane.y);
    }
}

static void draw(void) {
    int i;
    double now = al_get_time();
    float bgdx = parallaxPxs/2*(plane.x/SCREEN_W) - parallaxPxs/2;
    float bgdy = (now - game_start_timestamp - total_paused_time)/MAX_GAMETIME*4*SCREEN_H - 3*SCREEN_H + parallaxPxs/2*plane.y/SCREEN_H + parallaxPxs/2;
//    game_log("now %.2lf start %.2lf totalp %.2lf", now, game_start_timestamp, total_paused_time);
//game_log("%f", now);
    al_draw_bitmap(img_background, bgdx, bgdy, 0);

    // draw movable objects
    for (i=0; i<MAX_BULLET; i++)
        draw_movable_object(playerBullets[i]);
    for (i=0;i<MAX_ENEMY;i++) for (int j=0;j<MAX_ENEMY_BULLET;j++)
        draw_movable_object(enemyBullets[i][j]);
    // draw laser
    al_draw_filled_circle(plane.x, plane.y, 30*laser_charge, al_map_rgb(0,85,255));
    al_draw_filled_circle(plane.x, plane.y, 25*laser_charge, al_map_rgb(128,234,255));
    if(laser_charge>=1)
        al_draw_rotated_bitmap(img_laser, 10, 25, plane.x, plane.y, laser.angle, 0);

    draw_movable_object(plane);
    draw_movable_object(planeHealth);
    for (i = 0; i < MAX_ENEMY; i++) {
        draw_movable_object(enemies[i]);
        draw_movable_object(enemyHealth[i]);
    }
    // mouse crosshair
    al_draw_bitmap(img_crosshair, mouse_x - al_get_bitmap_width(img_crosshair)/2, mouse_y - al_get_bitmap_height(img_crosshair)/2, 0);

    // HUD
    for (int j=0;j<=gameMode;j++) {
        al_draw_textf(font_pirulen_32, al_map_rgb(255, 0, 0), 20, 20 + j * 50, 0, "P%d %d", j+1, playerScore[j]);
    }
    al_draw_textf(font_pirulen_32, al_map_rgb(255, 0, 0), SCREEN_W*4/5, 20, 0, "Level %d", currentLevel);
    // Pause screen
    if (paused){
        al_draw_filled_rectangle(SCREEN_W*1/10, SCREEN_H*1/10, SCREEN_W*9/10, SCREEN_H*9/10, al_map_rgba(0, 0, 10, 200));
        al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 255), SCREEN_W/2, SCREEN_H*2.5/10, ALLEGRO_ALIGN_CENTER, "Paused");
        al_draw_text(font_pirulen_24, al_map_rgb(255, 255, 255), SCREEN_W/2, SCREEN_H*6/10, ALLEGRO_ALIGN_CENTER, "Press enter to resume");
    }
    float dur;
    dur = now-levelup_timestamp>0 ? now-levelup_timestamp : 0;
    al_draw_text(font_pirulen_24, al_map_rgba(255, 150, 10, 255*(1-(dur)/2)), SCREEN_W/2, SCREEN_H/2, ALLEGRO_ALIGN_CENTER, "LEVEL UP");

}


static void destroy(void) {
    al_destroy_bitmap(img_background);
    al_destroy_bitmap(img_plane);
    al_destroy_bitmap(img_enemy);
#ifdef audio
    al_destroy_sample(bgm);
    stop_bgm(bgm_id);
#endif
    al_destroy_bitmap(img_pBullets);
    game_log("Start scene destroyed");
}

static void on_key_down(int keycode) {
    if (keycode == ALLEGRO_KEY_TAB)
        draw_gizmos = !draw_gizmos;

}

static void on_mouse_down(int button, int x, int y, int arg){
    if (button == 1) {
        mouseleftdown = true;
        mouserightdown = false;
    }
    else if (button == 2) {
        mouseleftdown = false;
        mouserightdown = true;
    }
}

static void on_mouse_up(int button, int x, int y, int arg ){
    mouseleftdown = mouserightdown = false;
}

// TODO: Add more event callback functions such as keyboard, mouse, ...

// Functions without 'static', 'extern' prefixes is just a normal
// function, they can be accessed by other files using 'extern'.
// Define your normal function prototypes below.

// The only function that is shared across files.
Scene scene_start_create(void) {
    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    scene.id = 2;
    scene.name = "Start";
    scene.initialize = &init;
    scene.update = &update;
    scene.draw = &draw;
    scene.destroy = &destroy;
    scene.on_key_down = &on_key_down;
    scene.on_mouse_down = &on_mouse_down;
    scene.on_mouse_up = &on_mouse_up;
    game_log("Start scene created");
    return scene;
}