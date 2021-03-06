// [utility.h]
// you should put functions shared across files in this header.
// utility functions such as image processing, collision detection
// should be put here.

#ifndef SCENE_UTILITY_H
#define SCENE_UTILITY_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#ifdef audio
#include <allegro5/allegro_audio.h>
#endif
/* Utility functions */
#ifdef audio
// Load audio and check if failed.
// Supports .wav, .flac, .ogg, .it, .mod, .s3m, .xm.
ALLEGRO_SAMPLE *load_audio(const char *filename);

// Play audio once.
ALLEGRO_SAMPLE_ID play_audio(ALLEGRO_SAMPLE *sample, float volume);

// Play audio loop.
ALLEGRO_SAMPLE_ID play_bgm(ALLEGRO_SAMPLE *sample, float volume);

// Stop audio.
void stop_bgm(ALLEGRO_SAMPLE_ID sample);
#endif

// Load font and check if failed.
// Supports .ttf.
ALLEGRO_FONT *load_font(const char *filename, int size);

// Load bitmap and check if failed.
// Supports .bmp, .pcx, .tga, .jpg, .png.
ALLEGRO_BITMAP *load_bitmap(const char *filename);

// Load resized bitmap and check if failed.
ALLEGRO_BITMAP *load_bitmap_resized(const char *filename, int w, int h);

// Concat strings for pathnames
char *concat(const char *s1, const char *s2);

// [HACKATHON 3-2]
// TODO: Declare a function.
// Determines whether the point (px, py) is in rect (x, y, w, h).
// Uncomment the code below.
bool pnt_in_rect(float px, float py, float x, float y, float w, float h);
// TODO: More functions that can be reused across different scenes.

bool pnt_in_ellipse(float px, float py, float x, float y, float w, float h);

bool bx_in_bx(float px, float py, int pw, int ph, float x, float y, int w, int h);

float easeOutQuad(float progress);

void ascii_to_chars(int val, int operation, char* target);

void read_score(void);

void save_score(void);

void update_score(void);

void sort_scores();

#endif