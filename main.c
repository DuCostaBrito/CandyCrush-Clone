#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <time.h>
#include "candy.h"

#define BOARD_SIZE 8

void must_init(bool test, const char *description)
{
    if (test)
        return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

bool within(int top, int bottom, int x)
{
    if ((x >= bottom) && (x <= top))
        return true;
    else
        return false;
}

int main()
{
    srand(time(0));
    BOARD *board = createBoard();
    int width = 570;
    int height = 1024;

    bool done = false;
    int pos_x = width / 2;
    int pos_y = height / 2;

    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;

    ALLEGRO_COLOR color;

    if (!al_init())
        return -1;
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    display = al_create_display(width, height);

    if (!display)
        return -1;

    al_init_primitives_addon();
    // Declarando mouse e teclado
    al_install_keyboard();
    al_install_mouse();

    queue = al_create_event_queue();

    // Deixando a fila atenta aos eventos do teclado e mouse
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    while (!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                done = true;
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
        }

        al_draw_filled_rounded_rectangle(50, 150, width - 50, height - 50, 40, 40, al_map_rgba(0, 0, 0, 100));
        drawBoard(board);
        al_flip_display();                            // Buffer
        al_clear_to_color(al_map_rgb(150, 150, 150)); // Limpa o plano de fundo para preto
    }
    al_destroy_display(display);
}