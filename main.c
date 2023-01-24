#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <time.h>
#include "candy.h"

#define FPS 60
#define KEY_SEEN 1
#define KEY_RELEASED 2

void must_init(bool test, const char *description)
{
    if (test)
        return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

ALLEGRO_BITMAP* sprite_grab(int x, int y, int w, int h, ALLEGRO_BITMAP *spriteSheet)
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(spriteSheet, x, y, w, h);
    must_init(sprite, "sprite grab");
    return sprite;
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
    int i, j;

    bool done = false;
    bool redraw = true;

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    int xMouse, xMouseOrigin, xMouseEnd;
    int yMouse, yMouseOrigin, yMouseEnd;
    bool mousePressed = false;
    int srcIndexCandyX, srcIndexCandyY;
    int destIndexCandyX, destIndexCandyY;

    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;

    ALLEGRO_COLOR color;

    if (!al_init())
        return -1;
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    display = al_create_display(width, height);

    if (!display)
        return -1;

    timer = al_create_timer(1.0 / FPS);
    if (!timer)
        return -1;

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

    //getting images
    ALLEGRO_BITMAP  *background = al_load_bitmap("resources/images/background.png");
    ALLEGRO_BITMAP *spriteSheet = al_load_bitmap("resources/images/candy_fruits.png");
    ALLEGRO_BITMAP *sprites[8];
    sprites[0] = sprite_grab(0, 0, 70, 70, spriteSheet);
    sprites[1] = sprite_grab(70, 0, 70, 70, spriteSheet);
    sprites[2] = sprite_grab(0, 70, 70, 70, spriteSheet);
    sprites[3] = sprite_grab(70, 70, 70, 70, spriteSheet);
    sprites[4] = sprite_grab(140, 70, 70, 70, spriteSheet);
    sprites[5] = sprite_grab(140, 140, 70, 70, spriteSheet);
    sprites[6] = sprite_grab(0, 140, 70, 70, spriteSheet);
    sprites[7] = sprite_grab(140, 0, 70, 70, spriteSheet);

    ALLEGRO_EVENT ev;
    al_start_timer(timer);

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
                //testando se foi tentado mexer com uma peca adjacente (nao diagonal) 
                if ((((destIndexCandyX == srcIndexCandyX + 1) || (destIndexCandyX == srcIndexCandyX - 1)) && (destIndexCandyY == srcIndexCandyY)) ||
                (((destIndexCandyY == srcIndexCandyY + 1) || (destIndexCandyY == srcIndexCandyY - 1)) && (destIndexCandyX == srcIndexCandyX)))
                    changeColors(board, srcIndexCandyX, srcIndexCandyY, destIndexCandyX, destIndexCandyY, background, sprites);
                mousePressed = false;
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
            // al_draw_filled_rounded_rectangle(50, 150, width - 50, height - 50, 40, 40, al_map_rgba(0, 0, 0, 100));
            al_draw_bitmap(background, 0, 0, 0);
            drawBoard(board, sprites);
            al_flip_display(); // Buffer
            redraw = false;
        }
    }
    al_destroy_bitmap(background);
    al_destroy_bitmap(sprites[0]);
    al_destroy_bitmap(sprites[1]);
    al_destroy_bitmap(sprites[2]);
    al_destroy_bitmap(sprites[3]);
    al_destroy_bitmap(sprites[4]);
    al_destroy_bitmap(sprites[5]);
    al_destroy_bitmap(sprites[6]);
    al_destroy_bitmap(sprites[7]);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    return 0;
}