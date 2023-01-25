#ifndef _AUDIO_
#define _AUDIO_

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

void audio_init(ALLEGRO_SAMPLE *sample_bg, ALLEGRO_SAMPLE *sample_mult[5], ALLEGRO_SAMPLE *sample_clear, ALLEGRO_SAMPLE *sample_wrong_play);

#endif