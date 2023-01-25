#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include <time.h>
#include "candy.h"
#include "global.h"
#include "init.h"

int main()
{
    srand(time(0));
    board = createBoard();
    int i, j;
    int w = 1;
    bool verified = true;

    bool done = false;
    bool redraw = true;

    memset(key, 0, sizeof(key));

    int xMouse, xMouseOrigin, xMouseEnd;
    int yMouse, yMouseOrigin, yMouseEnd;
    bool mousePressed = false;
    int srcIndexCandyX, srcIndexCandyY;
    int destIndexCandyX, destIndexCandyY;

    game_init();
    bg_instance = al_create_sample_instance(sample_bg);
    al_set_sample_instance_playmode(bg_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(bg_instance, al_get_default_mixer());
    ALLEGRO_EVENT ev;
    al_start_timer(timer);
    
    al_play_sample_instance(bg_instance);
    while (verifyMatch(board) || isEmpty(board))
    {
        fallBoard(board, sprites);
        fillBoard(board, sprites);
    }
    while (1)
    {
        al_wait_for_event(queue, &ev);
        switch (ev.type)
        {
        case ALLEGRO_EVENT_TIMER:
            
            if (key[ALLEGRO_KEY_ESCAPE])
                done = true;
            for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;
            if (mousePressed)
            {
                for (i = 0; i < BOARD_ROW; i++)
                {
                    for (j = 0; j < BOARD_COL; j++)
                    {
                        if ((within(board->grid[i][j]->x + 70, board->grid[i][j]->x, xMouseOrigin)) && (within(board->grid[i][j]->y + 70, board->grid[i][j]->y, yMouseOrigin)))
                        {
                            srcIndexCandyX = i;
                            srcIndexCandyY = j;
                        }
                        else if ((within(board->grid[i][j]->x + 70, board->grid[i][j]->x, xMouseEnd)) && (within(board->grid[i][j]->y + 70, board->grid[i][j]->y, yMouseEnd)))
                        {
                            destIndexCandyX = i;
                            destIndexCandyY = j;
                        }
                    }
                }
                // testando se foi tentado mexer com uma peca adjacente (nao diagonal)
                if ((((destIndexCandyX == srcIndexCandyX + 1) || (destIndexCandyX == srcIndexCandyX - 1)) && (destIndexCandyY == srcIndexCandyY)) ||
                    (((destIndexCandyY == srcIndexCandyY + 1) || (destIndexCandyY == srcIndexCandyY - 1)) && (destIndexCandyX == srcIndexCandyX)))
                {
                    swipeColors(board, srcIndexCandyX, srcIndexCandyY, destIndexCandyX, destIndexCandyY, sprites);
                    if (!verifyMatch(board)){
                        swipeColors(board, srcIndexCandyX, srcIndexCandyY, destIndexCandyX, destIndexCandyY, sprites);
                        al_play_sample(sample_wrong_play, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }

                }
                mousePressed = false;
                // Se nao for uma jogada valida

                // Ajusta o tabuleiro
                while (verifyMatch(board) || isEmpty(board))
                {
                    fallBoard(board, sprites);
                    fillBoard(board, sprites);
                }
            }
            redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            key[ev.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[ev.keyboard.keycode] &= KEY_RELEASED;
            break;
        case ALLEGRO_EVENT_MOUSE_AXES:
            xMouse = ev.mouse.x;
            yMouse = ev.mouse.y;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            xMouseOrigin = ev.mouse.x;
            yMouseOrigin = ev.mouse.y;
            mousePressed = false;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            xMouseEnd = ev.mouse.x;
            yMouseEnd = ev.mouse.y;
            mousePressed = true;
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }
        if (done)
            break;
        if (redraw && al_is_event_queue_empty(queue))
        {
            
            al_draw_bitmap(sprites[18], 0, 0, 0);
            showScore(sprites, board);
            drawBoard(board, sprites);
            al_flip_display(); // Buffer
            redraw = false;
        }
    }
    al_destroy_sample(sample_bg);
    al_destroy_sample(sample_clear);
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
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    return 0;
}