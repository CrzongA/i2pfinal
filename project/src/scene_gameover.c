//
// Created by leon on 17/1/2021.
//

#include "scene_gameover.h"
#include "../include/scene_menu.h"
#include "../include/scene_start.h"
#include "../include/utility.h"
#include "../include/shared.h"
#include "../include/game.h"
#include <stdio.h>

static const char* header = "Game Over!";
static const char* scoreheader = "Score: %d";
static const char* leaderbheader = "Leaderboard";
static const char* highestHint = "New Highscore!";
static const char* hint = "Press ESC to quit, Enter to restart";
static ALLEGRO_BITMAP *img_background ;
static double scene_gameover_timestamp;

static void init(void){
    scene_gameover_timestamp = al_get_time();
    img_background = load_bitmap_resized(concat(img_path,gobgs[0]), SCREEN_W, SCREEN_H);
    // sort and save highscores into save.txt.
    update_score();
    save_score();
}

static void update(void){

}

static void draw(void) {
//    al_draw_tinted_bitmap(img_background,al_map_rgba(0,0,0,10), 0, 0, 0);
    al_draw_bitmap(img_background, 0, 0, 0);
    al_draw_text(font_pirulen_32, al_map_rgb(255,0, 0), SCREEN_W/2, 20, ALLEGRO_ALIGN_CENTER, header);
    al_draw_textf(font_pirulen_32, al_map_rgb(255,0, 80), SCREEN_W/2, 100, ALLEGRO_ALIGN_CENTER, scoreheader, playerScore[0]);
    if(gameMode==0)
        if(playerScore[0]>=highscores[0])
            al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 25), SCREEN_W/2, 150, ALLEGRO_ALIGN_CENTER, highestHint);
    al_draw_text(font_pirulen_24, al_map_rgb(255,0, 255), SCREEN_W/4, SCREEN_H*3/5-50, 0, leaderbheader);
    al_draw_text(font_pirulen_24, al_map_rgb(255,0, 60), SCREEN_W/2, SCREEN_H * 9/10, ALLEGRO_ALIGN_CENTER, hint);
    for (int i=0;i<3;i++)
        if(highscores[i]>0)
            al_draw_textf(font_pirulen_18, al_map_rgb(255, 255, 255), SCREEN_W/4+20, SCREEN_H*3/5+30*i, 0, "Rank %d  %d", i+1, highscores[i]);
}

static void on_key_down(int keycode) {
    if (keycode == ALLEGRO_KEY_ESCAPE)
        interrupt_sig=1;
    else if (keycode == ALLEGRO_KEY_ENTER || keycode == ALLEGRO_KEY_PAD_ENTER)
        game_change_scene(scene_menu_create());
}

// The only function that is shared across files.
Scene scene_gameover_create(void) {
    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    scene.id = 3;
    scene.name = "Gameover";
    scene.update = &update;
    scene.initialize = &init;
    scene.draw = &draw;
    scene.on_key_down = &on_key_down;
    game_log("Settings scene created");
    return scene;
}
