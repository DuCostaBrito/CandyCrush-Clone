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
#include "states.h"

int main()
{
    srand(time(0));
    state = INICIO;
    while (state)
    {
        
        switch (state)
        {
        case INICIO:
            
            state_init();
            break;
        case MENU:
            
            state_menu();
            break;
        case JOGANDO:
            
            state_play();
            break;
        case FIM:
            state_fim();
            break;
        default:
            break;
        }
    }

    return 0;
}