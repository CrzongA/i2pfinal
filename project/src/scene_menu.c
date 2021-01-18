#include "../include/scene_menu.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#ifdef audio
#include <allegro5/allegro_acodec.h>
#endif
#include "../include/game.h"
#include "../include/utility.h"
#include "../include/shared.h"
#include "../include/scene_start.h"
#include "../include/scene_settings.h"

// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */


// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.

static const char* txt_title = "Orbital Vanguard";
static const char* txt_hint = "Destiny Awaits.";
static const char* txt_info = "Press enter key to start";
static ALLEGRO_BITMAP* img_background;
static ALLEGRO_BITMAP *img_settings;
static ALLEGRO_BITMAP *img_settings2;
static double bg_colors[3]={1, 1, 1};
static bool color_dir[3] = {true};
#ifdef audio
static ALLEGRO_SAMPLE* bgm;
static ALLEGRO_SAMPLE_ID bgm_id;
#endif

static void init(void);
static void draw(void);
static void destroy(void);
static void on_key_down(int keycode);

static void init(void) {
    // read highscores into buffer.
    read_score();
    sort_scores();
    img_background = load_bitmap_resized(concat(img_path,mainbgs[2]), SCREEN_W, SCREEN_H);
    img_settings = al_load_bitmap(concat(img_path,"settings.png"));
    img_settings2 = al_load_bitmap(concat(img_path, "settings2.png"));
    // Can be moved to shared_init to decrease loading time.
#ifdef audio
    bgm = load_audio(concat(audio_path,"S31-Night Prowler.ogg"));
    bgm_id = play_bgm(bgm, 1);
#endif
    game_log("Menu scene initialized");
}

static void update(void){
    // background color tint loop
    for (int i=0;i<3;i++) {
        if (bg_colors[i] > 1) {color_dir[i]=true; bg_colors[i]=1;}
        else if (bg_colors[i] < 0.5) {color_dir[i]=false; bg_colors[i]=0.5;}
        if(color_dir[i]) bg_colors[i]-=0.001*(i+1);
        else bg_colors[i]+=0.001*(i+1);
    }
}

static void draw(void) {
//    al_draw_bitmap(img_background, 0, 0, 0);
    al_draw_tinted_bitmap(img_background, al_map_rgba_f(bg_colors[0], bg_colors[1], bg_colors[2], 1), 0, 0, 0);
    // [HACKATHON 3-5]
    // TODO: Draw settings images.
    // The settings icon should be located at (x, y, w, h) =
    // (SCREEN_W - 48, 10, 38, 38).
    // Change its image according to your mouse position.
    // Uncomment and fill in the code below.
    if (pnt_in_rect(mouse_x, mouse_y, SCREEN_W-48, 10, 38, 38))
        al_draw_bitmap(img_settings2, SCREEN_W-48, 10, 0);
    else
        al_draw_bitmap(img_settings, SCREEN_W-48, 10, 0);
    al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 255), SCREEN_W / 2, 30, ALLEGRO_ALIGN_CENTER, txt_title);
    al_draw_text(font_pirulen_24, al_map_rgb(220, 220, 255), SCREEN_W / 2, 120, ALLEGRO_ALIGN_CENTER, txt_hint);
    al_draw_text(font_pirulen_24, al_map_rgb(255, 255, 255), 20, SCREEN_H - 50, 0, txt_info);
}

static void destroy(void) {
#ifdef audio
    al_destroy_sample(bgm);
    stop_bgm(bgm_id);
#endif
    al_destroy_bitmap(img_background);
    // [HACKATHON 3-6]
    // TODO: Destroy the 2 settings images.
    // Uncomment and fill in the code below.
    al_destroy_bitmap(img_settings);
    al_destroy_bitmap(img_settings2);
    game_log("Menu scene destroyed");
}

static void on_key_down(int keycode) {
    if (keycode == ALLEGRO_KEY_ENTER || keycode == ALLEGRO_KEY_PAD_ENTER)
        game_change_scene(scene_start_create());
}

// [HACKATHON 3-7]
// TODO: When settings clicked, switch to settings scene.
// Uncomment and fill in the code below.
static void on_mouse_down(int btn, int x, int y, int dz) {
    if (btn == 1) {
        if (pnt_in_rect(x, y, SCREEN_W-48, 10, 38, 38))
            game_change_scene(scene_settings_create());
    }
}

// TODO: Add more event callback functions such as update, ...

// Functions without 'static', 'extern' prefixes is just a normal
// function, they can be accessed by other files using 'extern'.
// Define your normal function prototypes below.

// The only function that is shared across files.
Scene scene_menu_create(void) {
    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    scene.id = 1;
    scene.name = "Menu";
    scene.initialize = &init;
    scene.update = &update;
    scene.draw = &draw;
    scene.destroy = &destroy;
    scene.on_key_down = &on_key_down;
    // [HACKATHON 3-8]
    // TODO: Register on_mouse_down.
    // Uncomment the code below.
    scene.on_mouse_down = &on_mouse_down;
    // TODO: Register more event callback functions such as update, mouse, ...
    game_log("Menu scene created");
    return scene;
}
