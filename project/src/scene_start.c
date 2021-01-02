#include "../include/scene_start.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "../include/game.h"
#include "../include/utility.h"
#include <math.h>

// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */

// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.

static ALLEGRO_BITMAP* img_background;
static ALLEGRO_BITMAP* img_plane;
static ALLEGRO_BITMAP* img_enemy;
// [HACKATHON 2-1]
// TODO: Declare a variable to store your bullet's image.
// Uncomment and fill in the code below.
static ALLEGRO_BITMAP* img_bullet;

typedef struct {
    // The center coordinate of the image.
    float x, y;
    // The width and height of the object.
    float w, h;
    // The velocity in x, y axes.
    float vx, vy;
    // Timestamp of initialization of the object.
    double initT, xVelCoef;
    // Should we draw this object on the screen.
    bool hidden;
    // The pointer to the object’s image.
    ALLEGRO_BITMAP* img;
} MovableObject;

static void init(void);
static void update(void);
static void draw_movable_object(MovableObject obj);
static void draw(void);
static void destroy(void);
static double enemy_movement(double, double, double);

#define MAX_ENEMY 3
// [HACKATHON 2-2]
// TODO: Declare the max bullet count that will show on screen.
// You can try max 4 bullets here and see if you needed more.
// Uncomment and fill in the code below.
#define MAX_BULLET 4
static MovableObject plane;
static MovableObject enemies[MAX_ENEMY];
// [HACKATHON 2-3]
// TODO: Declare an array to store bullets with size of max bullet count.
// Uncomment and fill in the code below.
static MovableObject bullets[MAX_BULLET];
// [HACKATHON 2-4]
// TODO: Set up bullet shooting cool-down variables.
// 1) Declare your shooting cool-down time as constant. (0.2f will be nice)
// 2) Declare your last shoot timestamp.
// Uncomment and fill in the code below.
static const float MAX_COOLDOWN = 0.2;
static double last_shoot_timestamp;
#ifdef audio
static ALLEGRO_SAMPLE* bgm;
static ALLEGRO_SAMPLE_ID bgm_id;
#endif
static bool draw_gizmos;

static void init(void) {
    int i;
    img_background = load_bitmap_resized(concat(img_path,"start-bg.jpg"), SCREEN_W, SCREEN_H);
    img_plane = plane.img = load_bitmap(concat(img_path,"plane.png"));
    plane.x = 400;
    plane.y = 500;
    plane.w = al_get_bitmap_width(plane.img);
    plane.h = al_get_bitmap_height(plane.img);
    img_enemy = load_bitmap(concat(img_path,"smallfighter0006.png"));
    for (i = 0; i < MAX_ENEMY; i++) {
        enemies[i].img = img_enemy;
        enemies[i].w = al_get_bitmap_width(img_enemy);
        enemies[i].h = al_get_bitmap_height(img_enemy);
        enemies[i].initT = al_get_time();
        enemies[i].xVelCoef = (rand()/(double)RAND_MAX) * 10;
        enemies[i].vx = (rand()/(float)RAND_MAX) * 2;
        enemies[i].vy = (rand()/(float)RAND_MAX) * 1;
        enemies[i].x = enemies[i].w / 2 + (float)rand() / RAND_MAX * (SCREEN_W - enemies[i].w);
        enemies[i].y = 80;
    }

    img_bullet = al_load_bitmap(concat(img_path,"image12.png"));
    for (i=0; i<MAX_BULLET; i++) {
        bullets[i].img = img_bullet;
        bullets[i].w = al_get_bitmap_width(img_bullet);
        bullets[i].h = al_get_bitmap_height(img_bullet);
        bullets[i].vx = 0;
        bullets[i].vy = -5;
        bullets[i].hidden = true;
    }
#ifdef audio
    // Can be moved to shared_init to decrease loading time.
    bgm = load_audio(concat(audio_path,"mythica.ogg"));
    game_log("Start scene initialized");
    bgm_id = play_bgm(bgm, 1);
#endif
}

static void update(void) {
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
    plane.y += plane.vy * 4 * (plane.vx ? 0.71f : 1);
    plane.x += plane.vx * 4 * (plane.vy ? 0.71f : 1);

    if (plane.x - plane.w/2 < 0)
        plane.x = plane.w/2;
    else if (plane.x + plane.w/2 > SCREEN_W)
        plane.x = SCREEN_W - plane.w/2;
    if (plane.y - plane.h/2 < 0)
        plane.y = plane.h/2;
    else if (plane.y + plane.h/2 > SCREEN_H)
        plane.y = SCREEN_H - plane.h/2;

    int i;
    for (i=0; i < MAX_BULLET; i++) {
        if (bullets[i].hidden)
            continue;
        bullets[i].x += bullets[i].vx;
        bullets[i].y += bullets[i].vy;
        if (bullets[i].y < 0 || bullets[i].h > SCREEN_H)
            bullets[i].hidden = true;
    }

    // update bullet position
    double now = al_get_time();
    if (key_state[ALLEGRO_KEY_SPACE] && (now - last_shoot_timestamp >= MAX_COOLDOWN)) {
        for (i = 0; i < MAX_BULLET ; i++) {
            if (bullets[i].hidden) {
                last_shoot_timestamp = now;
                bullets[i].hidden = false;
                bullets[i].x = plane.x;
                bullets[i].y = plane.y;
                break;
            }
        }
    }

    // update enemy position
    for (int i=0; i<MAX_ENEMY; i++){
        enemies[i].vx = enemy_movement(enemies[i].initT, enemies[i].xVelCoef, enemies[i].vx);
//        enemies[i].vy = 0.5;
        if (!enemies[i].hidden){
            enemies[i].x += enemies[i].vx;
            enemies[i].y += enemies[i].vy;
        }
    }

    // bullet-enemy collision detection
    for (i=0; i<MAX_ENEMY; i++) {
        for (int j = 0; j < MAX_BULLET; j++) {
            if (pnt_in_rect(bullets[j].x, bullets[j].y, enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h)) {
                enemies[i].hidden = false;
                enemies[i].y = 80;
                enemies[i].x = enemies[i].w / 2 + (float) rand() / RAND_MAX * (SCREEN_W - enemies[j].w);
            }
        }
    }

    //enemy-player collision detection
    for (i=0; i<MAX_ENEMY;i++){
        if (pnt_in_rect(plane.x, plane.y, enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h)){
            game_log("player hit");
        }

    }
}

double enemy_movement(double initTime, double xVel, double vx){
    return xVel * sin(vx * (al_get_time() - initTime));
}

static void draw_movable_object(MovableObject obj) {
    if (obj.hidden)
        return;
    al_draw_bitmap(obj.img, round(obj.x - obj.w / 2), round(obj.y - obj.h / 2), 0);
    if (draw_gizmos) {
        al_draw_rectangle(round(obj.x - obj.w / 2), round(obj.y - obj.h / 2),
            round(obj.x + obj.w / 2) + 1, round(obj.y + obj.h / 2) + 1, al_map_rgb(255, 0, 0), 0);
    }
}

static void draw(void) {
    int i;
    al_draw_bitmap(img_background, 0, 0, 0);
    // [HACKATHON 2-8]
    // TODO: Draw all bullets in your bullet array.
    // Uncomment and fill in the code below.
    for (i=0; i<MAX_BULLET; i++)
        draw_movable_object(bullets[i]);
    draw_movable_object(plane);
    for (i = 0; i < MAX_ENEMY; i++)
        draw_movable_object(enemies[i]);
}

static void destroy(void) {
    al_destroy_bitmap(img_background);
    al_destroy_bitmap(img_plane);
    al_destroy_bitmap(img_enemy);
#ifdef audio
    al_destroy_sample(bgm);
    stop_bgm(bgm_id);
#endif
    // [HACKATHON 2-9]
    // TODO: Destroy your bullet image.
    // Uncomment and fill in the code below.
    al_destroy_bitmap(img_bullet);
    game_log("Start scene destroyed");
}

static void on_key_down(int keycode) {
    if (keycode == ALLEGRO_KEY_TAB)
        draw_gizmos = !draw_gizmos;
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
    // TODO: Register more event callback functions such as keyboard, mouse, ...
    game_log("Start scene created");
    return scene;
}