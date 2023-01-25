#include "audio.h"

void audio_init(ALLEGRO_SAMPLE *sample_bg, ALLEGRO_SAMPLE *sample_mult[5], ALLEGRO_SAMPLE *sample_clear, ALLEGRO_SAMPLE *sample_wrong_play)
{
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(8);

    sample_bg = al_load_sample("resources/music/monkey_drama.mp3");

    sample_clear = al_load_sample("resources/sounds/clear.mp3");

    sample_wrong_play = al_load_sample("resources/sounds/wrong_move.ogg");
    if (sample_wrong_play)
        printf("OI\n");
    sample_mult[0] = al_load_sample("resources/sounds/multi_2.mp3");
    sample_mult[1] = al_load_sample("resources/sounds/multi_3.mp3");
    sample_mult[2] = al_load_sample("resources/sounds/multi_4.mp3");
    sample_mult[3] = al_load_sample("resources/sounds/multi_5.mp3");
    sample_mult[4] = al_load_sample("resources/sounds/multi_6.mp3");
}