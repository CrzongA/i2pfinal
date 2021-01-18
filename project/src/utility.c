// [utility.c]
// you should implement the utility functions defined in the header.

#include <string.h>
#include <stdio.h>
#include <math.h>
#include "../include/utility.h"
#include "../include/game.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#ifdef audio
#include <allegro5/allegro_audio.h>
#endif
#include "../include/game.h"
#include "stdlib.h"
#include "string.h"

#ifdef audio
ALLEGRO_SAMPLE* load_audio(const char* filename) {
    ALLEGRO_SAMPLE* sample = al_load_sample(filename);
    if (!sample)
        game_abort("failed to load audio: %s", filename);
    else
        game_log("loaded audio: %s", filename);
    return sample;
}

ALLEGRO_SAMPLE_ID play_audio(ALLEGRO_SAMPLE* sample, float volume) {
    ALLEGRO_SAMPLE_ID id;
    if (!al_play_sample(sample, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &id))
        game_abort("failed to play audio (once)");
    else
        game_log("played audio (once)");
    return id;
}

ALLEGRO_SAMPLE_ID play_bgm(ALLEGRO_SAMPLE* sample, float volume) {
    ALLEGRO_SAMPLE_ID id;
    if (!al_play_sample(sample, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &id))
        game_abort("failed to play audio (bgm)");
    else
        game_log("played audio (bgm)");
    return id;
}

void stop_bgm(ALLEGRO_SAMPLE_ID sample) {
    al_stop_sample(&sample);
    game_log("stop audio (bgm)");
}
#endif

ALLEGRO_FONT* load_font(const char* filename, int size) {
    ALLEGRO_FONT* font = al_load_font(filename, size, 0);
    if (!font)
        game_abort("failed to load font: %s with size %d", filename, size);
    else
        game_log("loaded font: %s with size %d", filename, size);
    return font;
}

ALLEGRO_BITMAP* load_bitmap(const char* filename) {
    ALLEGRO_BITMAP* bmp = al_load_bitmap(filename);
    if (!bmp)
        game_abort("failed to load image: %s", filename);
    else
        game_log("loaded image: %s", filename);
    return bmp;
}

ALLEGRO_BITMAP *load_bitmap_resized(const char *filename, int w, int h) {
    ALLEGRO_BITMAP* loaded_bmp = load_bitmap(filename);
    ALLEGRO_BITMAP *resized_bmp = al_create_bitmap(w, h);
    ALLEGRO_BITMAP *prev_target = al_get_target_bitmap();

    if (!resized_bmp)
        game_abort("failed to create bitmap when creating resized image: %s", filename);
    al_set_target_bitmap(resized_bmp);
    al_draw_scaled_bitmap(loaded_bmp, 0, 0,
        al_get_bitmap_width(loaded_bmp),
        al_get_bitmap_height(loaded_bmp),
        0, 0, w, h, 0);
    al_set_target_bitmap(prev_target);
    al_destroy_bitmap(loaded_bmp);

    game_log("resized image: %s", filename);

    return resized_bmp;
}

// handle string concatenation in processing pathnames
char* concat(const char *s1, const char *s2){
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    if (result==NULL){game_log("String concatenation error: failed to malloc for char pointer\n"); return NULL;}
    memcpy(result,s1,len1);
    memcpy(result + len1, s2, len2 + 1);
    return result;
}

// [HACKATHON 3-3]
// TODO: Define bool pnt_in_rect(int px, int py, int x, int y, int w, int h)
// Uncomment and fill in the code below.
bool pnt_in_rect(float px, float py, float x, float y, float w, float h) {
    return (px<x+w && px>x && py<y+h && py>y);
}

bool pnt_in_ellipse(float px, float py, float x, float y, float w, float h){
    return pow(px-x, 2)/pow(w/2, 2) + pow(py-y, 2)/pow(h/2, 2) <= 1;
}

bool bx_in_bx(float px, float py, int pw, int ph, float x, float y, int w, int h){
    float targets[4][2] = {{px, py}, {px+pw, py+ph}, {px+pw, py}, {px, py+ph}};
    for (int i=0; i<4; i++){
        if(pnt_in_rect(targets[i][0], targets[i][1], x, y, w, h)) return true;
    }
    return false;
}

/* Return ease out animation function value */
float easeOutQuad(float progress){
    return 1 - ((1 - progress) * (1 - progress));
}

void ascii_to_chars(int val, int operation, char* target){
    char chars[10]={'\0'};
    if(operation==1){ //increment
        val++;
    }
    int rem=val, digits[10]={0}, n=0;
    if(rem==0) digits[0]='0';
    while(rem>0){
        digits[n] = rem % 10;
        rem /= 10;
        n++;
    }
    for (int i=0, j=n; i<n; i++, j--){
        chars[i] = (char)(digits[j]+'0');
    }

    memcpy(target, chars, n+1);
}

void read_score(void){
    int buffer;
    int i=0;
    FILE *pFile = fopen("save.txt", "r");
    if (pFile){
        while(fscanf(pFile, "%d", &buffer)!=EOF){
            highscores[i] = buffer; //atoi(buffer)
//            game_log("[] score %d", i);
            i++;
        }
        fclose(pFile);
    }
}

void save_score(void){
    FILE *pFile = fopen("save.txt", "w");
    if(pFile){
        for (int i=0;i<10;i++)
            fprintf(pFile, "%d\n", highscores[i]);
        fclose(pFile);
    }
}

void update_score(){
    // put score of current run into the highscore array, then sort it
    if (gameMode==0) highscores[10] = playerScore[0];
    sort_scores();
}

void sort_scores() {
    int tmp,sorted;
    for (int i=0;i<10;i++) {
        sorted=1;
        for (int j = 0; j < 10; j++) {
            if (highscores[j] < highscores[j + 1]) {
                sorted = 0;
                tmp = highscores[j + 1];
                highscores[j + 1] = highscores[j];
                highscores[j] = tmp;
            }
        }
        if (sorted) break;
    }
    highscores[10]=0;
    game_log("highscores sorted");
}
