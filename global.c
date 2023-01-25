#include <stdio.h>

#include "global.h"

// ---------------------------- VARIAVEIS GLOBAIS ------------------------- //
BOARD               *board;
unsigned char       key[ALLEGRO_KEY_MAX];

// -------------- ALLEGRO ------------- //
ALLEGRO_DISPLAY     *display;
ALLEGRO_BITMAP      *sprites[19];
ALLEGRO_TIMER       *timer;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_SAMPLE *sample_bg;
ALLEGRO_SAMPLE *sample_mult[5];
ALLEGRO_SAMPLE *sample_clear;
ALLEGRO_SAMPLE *sample_wrong_play;

// ----------------------------- FUNCOES ---------------------------------- //
void must_init(bool test, const char *description)
{
    if (test)
        return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

ALLEGRO_BITMAP *sprite_grab(int x, int y, int w, int h, ALLEGRO_BITMAP *spriteSheet)
{
    ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(spriteSheet, x, y, w, h);
    must_init(sprite, "sprite grab");
    return sprite;
}

bool within(int top, int bottom, int x)
{
    if ((x >= bottom) && (x <= top))
        return true;
    else
        return false;
}

int aleat(int lo, int hi)
{
    return lo + (rand() % (hi - lo));
}