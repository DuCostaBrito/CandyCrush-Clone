#include "audio.h"

void audio_init()
{
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(16);

    sample_bg = al_load_sample("resources/music/monkey_drama.ogg");
    must_init(sample_bg, "background sound");
    sample_mult[0] = al_load_sample("resources/sounds/clear.ogg");
    must_init(sample_mult[0], "mult[0] sound");
    sample_wrong_play = al_load_sample("resources/sounds/wrong_move.ogg");
    must_init(sample_wrong_play, "wrong play sound");
    sample_mult[1] = al_load_sample("resources/sounds/multi_2.ogg");
    must_init(sample_mult[1], "mult[1] sound");
    sample_mult[2] = al_load_sample("resources/sounds/multi_3.ogg");
    must_init(sample_mult[2], "mult[2] sound");
    sample_mult[3] = al_load_sample("resources/sounds/multi_4.ogg");
    must_init(sample_mult[3], "mult[3] sound");
    sample_mult[4] = al_load_sample("resources/sounds/multi_5.ogg");
    must_init(sample_mult[4], "mult[4] sound");
    sample_mult[5] = al_load_sample("resources/sounds/multi_6.ogg");
    must_init(sample_mult[5], "mult[5] sound");
}