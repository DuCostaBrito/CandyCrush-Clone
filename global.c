#include <stdio.h>

#include "global.h"

// ---------------------------- VARIAVEIS GLOBAIS ------------------------- //
BOARD               *board;
unsigned char       key[ALLEGRO_KEY_MAX];
bool setting_on = false;
bool music_on = true;
bool sound_on = true;

// -------------- ALLEGRO ------------- //
ALLEGRO_DISPLAY     *display;
ALLEGRO_BITMAP      *sprites[N_SPRITES];
ALLEGRO_TIMER       *timer;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_SAMPLE *sample_bg;
ALLEGRO_SAMPLE *sample_mult[6];
ALLEGRO_SAMPLE *sample_wrong_play;
ALLEGRO_SAMPLE_INSTANCE *bg_instance;

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