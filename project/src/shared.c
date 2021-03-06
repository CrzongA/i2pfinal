// [shared.c]
// you should define the shared variable declared in the header here.

#include "../include/shared.h"
#include "../include/utility.h"
#include "../include/game.h"
#include "../include/scene_menu.h"

#define FONT_PATH resources/font

ALLEGRO_FONT* font_pirulen_32;
ALLEGRO_FONT* font_pirulen_24;
ALLEGRO_FONT* font_pirulen_18;
ALLEGRO_FONT* font_pirulen_15;

void shared_init(void) {
    font_pirulen_32 = load_font("resources/font/pirulen.ttf", 32);
    font_pirulen_24 = load_font("resources/font/pirulen.ttf", 24);
    font_pirulen_18 = load_font("resources/font/pirulen.ttf", 18);
    font_pirulen_15 = load_font("resources/font/pirulen.ttf", 15);
    game_change_scene(scene_menu_create());
}

void shared_destroy(void) {
    al_destroy_font(font_pirulen_32);
    al_destroy_font(font_pirulen_24);
    al_destroy_font(font_pirulen_18);
    al_destroy_font(font_pirulen_15);
}