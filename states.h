#ifndef _states_t_H
#define _states_t_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "candy.h"
#include "global.h"
#include "init.h"
#include "menu.h"

int itoa(int value, char *sp, int radix);
void state_init();
void state_menu();
void state_play();
void state_fim();

#endif