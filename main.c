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

int itoa(int value, char *sp, int radix)
{
    char tmp[16]; // be careful with the length of the buffer
    char *tp = tmp;
    int i;
    unsigned v;

    int sign = (radix == 10 && value < 0);
    if (sign)
        v = -value;
    else
        v = (unsigned)value;

    while (v || tp == tmp)
    {
        i = v % radix;
        v /= radix;
        if (i < 10)
            *tp++ = i + '0';
        else
            *tp++ = i + 'a' - 10;
    }

    int len = tp - tmp;

    if (sign)
    {
        *sp++ = '-';
        len++;
    }

    while (tp > tmp)
        *sp++ = *--tp;

    return len;
}
int main()
{
    srand(time(0));
    board = createBoard();
    int i, j;
    int mult = 0;
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
    while (verifyMatch(board, mult) || isEmpty(board))
    {
        fallBoard(board, sprites);
        fillBoard(board, sprites);
        mult++;
        if (mult >= 5)
            mult = 5;
    }
    while(!isPossible(board))
        shuffleBoard(board);
    mult = 0;
    while (1)
    {
        al_wait_for_event(queue, &ev);

        switch (ev.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (music_on)
                al_play_sample_instance(bg_instance);
            else
                al_stop_sample_instance(bg_instance);
            if (key[ALLEGRO_KEY_ESCAPE])
                done = true;
            for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;
            if (mousePressed)
            {
                mousePressed = false;
                if (within(450 + 70, 450, xMouseOrigin) && within(60 + 70, 60, yMouseOrigin))
                {
                    ALLEGRO_EVENT ev;
                    setting_on = !setting_on;
                    while (setting_on)
                    {
                        al_wait_for_event(queue, &ev);
                        switch (ev.type)
                        {
                        case ALLEGRO_EVENT_TIMER:
                            if (mousePressed)
                            {
                                if (within(450 + 70, 450, xMouseOrigin) && within(60 + 70, 60, yMouseOrigin))
                                {
                                    setting_on = !setting_on;
                                    mousePressed = false;
                                }
                                else if (within(450 + 70, 450, xMouseOrigin) && within(140 + 70, 140, yMouseOrigin))
                                {
                                    music_on = !music_on;
                                    mousePressed = false;
                                }
                                else if (within(450 + 70, 450, xMouseOrigin) && within(220 + 70, 220, yMouseOrigin))
                                {
                                    sound_on = !sound_on;
                                    mousePressed = false;
                                }
                                else if (within(450 + 70, 450, xMouseOrigin) && within(290 + 70, 290, yMouseOrigin))
                                {
                                    shuffleBoard(board);
                                    mousePressed = false;
                                }
                            }

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
                        }
                        redraw = true;
                        if (redraw && al_is_event_queue_empty(queue))
                        {
                            al_draw_bitmap(sprites[18], 0, 0, 0);
                            showScore(sprites, board);
                            drawBoard(board, sprites);
                            drawMenu();
                            al_flip_display(); // Buffer
                            redraw = false;
                        }
                    }
                }
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
                    if (!verifyMatch(board, mult))
                    {
                        swipeColors(board, srcIndexCandyX, srcIndexCandyY, destIndexCandyX, destIndexCandyY, sprites);
                        if (sound_on)
                            al_play_sample(sample_wrong_play, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                }
                // Se nao for uma jogada valida
                // Ajusta o tabuleiro
                while (verifyMatch(board, mult) || isEmpty(board))
                {
                    fallBoard(board, sprites);
                    fillBoard(board, sprites);
                    mult++;
                    if (mult >= 5)
                        mult = 5;
                }
                mult = 0;
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

        if (redraw && al_is_event_queue_empty(queue))
        {
            al_draw_bitmap(sprites[18], 0, 0, 0);
            showScore(sprites, board);
            drawBoard(board, sprites);
            drawSetting();
            al_flip_display(); // Buffer
            redraw = false;
            if (!isPossible(board))
            {
                done = true;
                char score[100];
                strcpy(score, "Seu score final foi: ");
                char snum[10];
                itoa(board->score, snum, 10);
                strcat(score, snum);
                al_show_native_message_box(display, "MATCH3", "FIM DE JOGO", score, NULL, 0);
            }
        }
        if (done)
            break;
    }
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
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    return 0;
}