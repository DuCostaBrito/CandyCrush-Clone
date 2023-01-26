#include "init.h"
#include "candy.h"


void game_init()
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
    sprites[19] = al_load_bitmap("resources/images/gui_settings.png");
    sprites[20] = al_load_bitmap("resources/images/gui_music_on.png");
    must_init(sprites[20], "20");
    sprites[21] = al_load_bitmap("resources/images/gui_music_off.png");
    must_init(sprites[21], "21");
    sprites[22] = al_load_bitmap("resources/images/gui_sound_on.png");
    must_init(sprites[22], "22");
    sprites[23] = al_load_bitmap("resources/images/gui_sound_off.png");
    must_init(sprites[23], "23");
    sprites[24] = al_load_bitmap("resources/images/gui_shuffle.png");
    must_init(sprites[24], "24");
    sprites[25] = al_load_bitmap("resources/images/gui_settings_on.png");
    must_init(sprites[25], "25");
    sprites[26] = al_load_bitmap("resources/images/play.png");
    must_init(sprites[26], "26");
    sprites[27] = al_load_bitmap("resources/images/logo.png");
    must_init(sprites[27], "27");
    sprites[28] = al_load_bitmap("resources/images/button.9.png");
    must_init(sprites[28], "28");
    sprites[29] = al_load_bitmap("resources/images/leaderboard.png");
    must_init(sprites[29], "29");
    
    //Audio
    audio_init();
    return;
}

void deinit(){
    al_destroy_sample(sample_bg);
    al_destroy_sample(sample_mult[5]);
    al_destroy_sample(sample_wrong_play);
    al_destroy_sample(sample_mult[0]);
    al_destroy_sample(sample_mult[1]);
    al_destroy_sample(sample_mult[2]);
    al_destroy_sample(sample_mult[3]);
    al_destroy_sample(sample_mult[4]);

    al_destroy_bitmap(sprites[0]);
    al_destroy_bitmap(sprites[1]);
    al_destroy_bitmap(sprites[2]);
    al_destroy_bitmap(sprites[3]);
    al_destroy_bitmap(sprites[4]);
    al_destroy_bitmap(sprites[5]);
    al_destroy_bitmap(sprites[6]);
    al_destroy_bitmap(sprites[7]);
    al_destroy_bitmap(sprites[8]);
    al_destroy_bitmap(sprites[9]);
    al_destroy_bitmap(sprites[10]);
    al_destroy_bitmap(sprites[11]);
    al_destroy_bitmap(sprites[12]);
    al_destroy_bitmap(sprites[13]);
    al_destroy_bitmap(sprites[14]);
    al_destroy_bitmap(sprites[15]);
    al_destroy_bitmap(sprites[16]);
    al_destroy_bitmap(sprites[17]);
    al_destroy_bitmap(sprites[18]);
    al_destroy_bitmap(sprites[18]);
    al_destroy_bitmap(sprites[19]);
    al_destroy_bitmap(sprites[20]);
    al_destroy_bitmap(sprites[21]);
    al_destroy_bitmap(sprites[22]);
    al_destroy_bitmap(sprites[23]);
    al_destroy_bitmap(sprites[24]);
    al_destroy_bitmap(sprites[25]);
    al_destroy_bitmap(sprites[26]);
    al_destroy_bitmap(sprites[27]);
    al_destroy_bitmap(sprites[28]);
    al_destroy_bitmap(sprites[29]);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    freeBoard();
}