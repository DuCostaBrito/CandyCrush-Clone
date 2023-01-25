#include "init.h"


void init()
{
    must_init(al_init(), "inicio");
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    display = al_create_display(WIDTH, HEIGHT);
    must_init(display, "display");
    timer = al_create_timer(1.0 / FPS);
    must_init(timer, "timer");

    al_init_primitives_addon();
    al_init_image_addon();
    // Declarando mouse e teclado
    al_install_keyboard();
    al_install_mouse();

    queue = al_create_event_queue();

    // Deixando a fila atenta aos eventos do teclado e mouse
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // getting images
    ALLEGRO_BITMAP *spriteSheet = al_load_bitmap("resources/images/candy_fruits.png");
    ALLEGRO_BITMAP *numberSheet = al_load_bitmap("resources/fonts/candy.png");
    sprites[0] = sprite_grab(149, 372, 38, 43, numberSheet);
    sprites[1] = sprite_grab(487, 70, 26, 43, numberSheet);
    sprites[2] = sprite_grab(0, 372, 36, 43, numberSheet);
    sprites[3] = sprite_grab(36, 372, 38, 43, numberSheet);
    sprites[4] = sprite_grab(440, 318, 36, 43, numberSheet);
    sprites[5] = sprite_grab(190, 372, 33, 43, numberSheet);
    sprites[6] = sprite_grab(76, 372, 35, 44, numberSheet);
    sprites[7] = sprite_grab(476, 318, 36, 43, numberSheet);
    sprites[8] = sprite_grab(371, 372, 35, 43, numberSheet);
    sprites[9] = sprite_grab(112, 373, 36, 43, numberSheet);
    sprites[10] = sprite_grab(0, 0, 70, 70, spriteSheet);
    sprites[11] = sprite_grab(70, 0, 70, 70, spriteSheet);
    sprites[12] = sprite_grab(70, 70, 70, 70, spriteSheet);
    sprites[13] = sprite_grab(70, 210, 70, 70, spriteSheet);
    sprites[14] = sprite_grab(140, 70, 70, 70, spriteSheet);
    sprites[15] = sprite_grab(140, 140, 70, 70, spriteSheet);
    sprites[16] = sprite_grab(0, 140, 70, 70, spriteSheet);
    sprites[17] = sprite_grab(140, 0, 70, 70, spriteSheet);
    sprites[18] = al_load_bitmap("resources/images/background.png");
    
    //Audio
    audio_init();
    return;
}