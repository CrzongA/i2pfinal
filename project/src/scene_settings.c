#include "../include/scene_settings.h"
#include "../include/scene_menu.h"
#include "../include/scene_start.h"
#include "../include/game.h"
#include "../include/utility.h"
#include "../include/shared.h"
#include <allegro5/allegro_primitives.h>

static const char* header = "Settings";
static const char* hint = "Press Backspace to return to menu, Enter to start";
//static const char* hint2 = "Press Enter to start";
static ALLEGRO_BITMAP *img_background ;
static ALLEGRO_BITMAP *ship_img[4];
static float w,h;

static void init(void){
    img_background = load_bitmap_resized(concat(img_path, mainbgs[1]), SCREEN_W, SCREEN_H);
    w = h = (float)SCREEN_H*2/10;
    for (int i=0; i<4;i++){
        ship_img[i] = load_bitmap_resized(concat(img_path, playerimg[i]), w, h);
    }
}

static void update(void){

}

static void draw(void) {
    al_draw_bitmap(img_background, 0, 0, 0);
    al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 255), SCREEN_W/2, SCREEN_H * 1/10, ALLEGRO_ALIGN_CENTER, header);
    al_draw_text(font_pirulen_15, al_map_rgb(255, 255, 255), SCREEN_W/2, SCREEN_H * 9/10, ALLEGRO_ALIGN_CENTER, hint);
    al_draw_textf(font_pirulen_15, al_map_rgb(255, 255, 255), SCREEN_W/2, SCREEN_H * 8/10, ALLEGRO_ALIGN_CENTER, "Ship %d is selected", playerShip+1);
    al_draw_filled_rectangle(SCREEN_W*2/10, SCREEN_H*2/10, SCREEN_W*2/10+w, SCREEN_H*2/10+h, al_map_rgba(255, 0, 170, 100));
    al_draw_bitmap(ship_img[0], SCREEN_W*2/10, SCREEN_H*2/10,0);
    al_draw_filled_rectangle(SCREEN_W*3.5/10, SCREEN_H*2/10, SCREEN_W*3.5/10+w, SCREEN_H*2/10+h, al_map_rgba(255, 0, 170, 100));
    al_draw_bitmap(ship_img[1], SCREEN_W*3.5/10, SCREEN_H*2/10,0);
    al_draw_filled_rectangle(SCREEN_W*5/10, SCREEN_H*2/10, SCREEN_W*5/10+w, SCREEN_H*2/10+h, al_map_rgba(255, 0, 170, 100));
    al_draw_bitmap(ship_img[2], SCREEN_W*5/10, SCREEN_H*2/10,0);
    al_draw_filled_rectangle(SCREEN_W*6.5/10, SCREEN_H*2/10, SCREEN_W*6.5/10+w, SCREEN_H*2/10+h, al_map_rgba(255, 0, 170, 100));
    al_draw_bitmap(ship_img[3], SCREEN_W*6.5/10, SCREEN_H*2/10,0);
}

static void on_key_down(int keycode) {
    if (keycode == ALLEGRO_KEY_BACKSPACE)
        game_change_scene(scene_menu_create());
    else if (keycode == ALLEGRO_KEY_ENTER || keycode == ALLEGRO_KEY_PAD_ENTER)
        game_change_scene(scene_start_create());
    else if (keycode == ALLEGRO_KEY_1 || keycode == ALLEGRO_KEY_PAD_1)
        playerShip=0;
    else if (keycode == ALLEGRO_KEY_2 || keycode == ALLEGRO_KEY_PAD_2)
        playerShip=1;
    else if (keycode == ALLEGRO_KEY_3 || keycode == ALLEGRO_KEY_PAD_3)
        playerShip=2;
    else if (keycode == ALLEGRO_KEY_4 || keycode == ALLEGRO_KEY_PAD_4)
        playerShip=3;


}

// The only function that is shared across files.
Scene scene_settings_create(void) {
    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    scene.id = 3;
    scene.name = "Settings";
    scene.update = &update;
    scene.initialize = &init;
    scene.draw = &draw;
    scene.on_key_down = &on_key_down;
    game_log("Settings scene created");
    return scene;
}