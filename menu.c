#include "menu.h"

void drawSetting(){
    al_draw_bitmap(sprites[19], 450, 60, 0);
}

void drawMenu(){
    if (setting_on)
        al_draw_bitmap(sprites[25], 450, 60, 0);
    else
        al_draw_bitmap(sprites[19], 450, 60, 0);
    if (music_on)
        al_draw_bitmap(sprites[20], 450, 140, 0);
    else    
        al_draw_bitmap(sprites[21], 450, 140, 0);
    if (sound_on)
        al_draw_bitmap(sprites[22], 450, 220, 0);
    else
        al_draw_bitmap(sprites[23], 450, 220, 0);
    al_draw_bitmap(sprites[24], 450, 290, 0);
}