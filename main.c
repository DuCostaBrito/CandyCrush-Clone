#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
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
    CANDY board[8][8];
    initializeBoard(board, 8);
    int width = 640;
    int height = 800;

    bool done = false;
    int pos_x = width / 2;
    int pos_y = height / 2;

    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;

    ALLEGRO_COLOR color;

    if (!al_init())
        return -1;

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

        al_draw_filled_rounded_rectangle(50, 50, 590, 750, 20, 20, al_map_rgba(0, 0, 0, 100));
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                switch (board[i][j].type)
                {
                    case 0:
                        color = al_map_rgb(220, 20, 60); 
                        break;
                    case 1:
                        color = al_map_rgb(238, 130, 238);
                        break;
                    case 2:
                        color = al_map_rgb(144, 238, 144);
                        break;
                    case 3:
                        color = al_map_rgb(255, 222, 173);
                        break;
                    case 4:
                        color = al_map_rgb(135, 206, 250);
                        break;
                    case 5:
                        color = al_map_rgb(139, 87, 66);
                    break;
                    case 6:
                        color = al_map_rgb(211, 211, 211);
                        break;
                    case 7:
                        color = al_map_rgb(0, 0, 0);
                        break;

                    default:
                        break;
                }
                al_draw_filled_circle(board[i][j].x, board[i][j].y, 20, color);
            }
        }
        al_flip_display();                            // Buffer
        al_clear_to_color(al_map_rgb(150, 150, 150)); // Limpa o plano de fundo para preto
    }
    al_destroy_display(display);
}