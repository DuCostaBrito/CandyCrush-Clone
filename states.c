#include "states.h"

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

void state_init()
{
    board = createBoard();

    memset(key, 0, sizeof(key));
    game_init();
    bg_instance = al_create_sample_instance(sample_bg);
    al_set_sample_instance_playmode(bg_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(bg_instance, al_get_default_mixer());

    al_start_timer(timer);
    state = MENU;
}

void state_menu()
{
    ALLEGRO_EVENT ev;

    bool done = false;
    bool redraw = true;
    bool play = false;
    int mult = 0;
    while (1)
    {
        while (!isPossible(board))
            shuffleBoard(board);
        al_wait_for_event(queue, &ev);

        switch (ev.type)
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                done = true;
            if (ev.keyboard.keycode == ALLEGRO_KEY_H)
                al_show_native_message_box(display, "MATCH3", "INFORMACOES", "Jogo estilo match3 desenvolvido na linguagem C e utilizando a biblioteca grafica ALLEGRO5\n Desenvolvido por Eduardo Costa Brito.", NULL, 0);
            if (ev.keyboard.keycode == ALLEGRO_KEY_F1)
                al_show_native_message_box(display, "MATCH3", "INSTRUCOES", "Jogo estilo match3 (Para ganhar pontos precisa formar no minimo trios do mesmo doce). \nPara mover um doce, basta clicar no doce escolhido e soltar na direcao que desejar mover.\n Para desligar a musica, sons de efeitos ou embaralhar o tabuleiro, clicar na ferramenta (canto direito superior) e desligar ou ligar o que desejar.\n O jogo termina quando nao ha mais jogadas possiveis", NULL, 0);
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            if (within(WIDTH / 2 - 140 + 240, WIDTH / 2 - 120, ev.mouse.x) && within(HEIGHT / 2 - 200 + 200, HEIGHT / 2 - 100, ev.mouse.y))
            {
                play = true;
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
            break;
        }
        if (done)
        {
            state = FIM;
            break;
        }
        if (play)
        {
            state = JOGANDO;
            break;
        }
        redraw = true;
        if (redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(PIXEL(222, 49, 99));
            al_draw_bitmap(sprites[26], WIDTH / 2 - 140, HEIGHT / 2 - 200, 0);
            al_draw_bitmap(sprites[29], WIDTH / 2 - 70, HEIGHT / 2 + 30, 0);
            al_draw_bitmap(sprites[27], WIDTH / 2 - 140, 50, 0);
            showRecord();
            al_flip_display(); // Buffer
            redraw = false;
        }
    }
}

// Laco principal, executa o jogo
void state_play()
{
    ALLEGRO_EVENT event;

    bool done = false;
    bool menu = false;
    bool redraw = true;
    int xMouse, xMouseOrigin, xMouseEnd;
    int yMouse, yMouseOrigin, yMouseEnd;
    bool mousePressed = false;
    int srcIndexCandyX, srcIndexCandyY;
    int destIndexCandyX, destIndexCandyY;
    int i, j;
    int mult = 0;
    ALLEGRO_EVENT ev;

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
                        case ALLEGRO_EVENT_DISPLAY_CLOSE:
                            setting_on = false;
                            done = true;
                            break;
                        case ALLEGRO_EVENT_KEY_UP:
                            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                            {
                                setting_on = false;
                                done = true;
                            }
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
                            showScore(board);
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
            if (ev.keyboard.keycode == ALLEGRO_KEY_H)
                al_show_native_message_box(display, "MATCH3", "INFORMACOES", "Jogo estilo match3 desenvolvido na linguagem C e utilizando a biblioteca grafica ALLEGRO5\n Desenvolvido por Eduardo Costa Brito.", NULL, 0);
            if (ev.keyboard.keycode == ALLEGRO_KEY_F1)
                al_show_native_message_box(display, "MATCH3", "INSTRUCOES", "Jogo estilo match3 (Para ganhar pontos precisa formar no minimo trios do mesmo doce). \nPara mover um doce, basta clicar no doce escolhido e soltar na direcao que desejar mover.\n Para desligar a musica, sons de efeitos ou embaralhar o tabuleiro, clicar na ferramenta (canto direito superior) e desligar ou ligar o que desejar.\n O jogo termina quando nao ha mais jogadas possiveis", NULL, 0);
            break;
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
        {
            state = FIM;
            break;
        }
        if (menu)
        {
            state = MENU;
            break;
        }
        if (redraw && al_is_event_queue_empty(queue))
        {
            al_draw_bitmap(sprites[18], 0, 0, 0);
            showScore(board);
            drawBoard(board, sprites);
            drawSetting();
            al_flip_display(); // Buffer
            redraw = false;
            if (!isPossible(board))
            {
                char score[100];
                strcpy(score, "Seu score final foi: ");
                char snum[6];
                itoa(board->score, snum, 10);
                strcat(score, snum);
                al_show_native_message_box(display, "MATCH3", "FIM DE JOGO", score, NULL, 0);
                menu = true;
                checkRecord(board->score);
                board->score = 0;
            }
        }
    }
}

void state_fim()
{
    deinit();
}