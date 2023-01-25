#ifndef _GLOBAL_
#define _GLOBAL_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>

// ----------- VARIAVEIS --------- //
#define WIDTH 570
#define HEIGHT 1024
#define FPS 60
#define BOARD_ROW 9
#define BOARD_COL 5
#define KEY_SEEN     1
#define KEY_RELEASED 2

// ---------------------------- TIPOS DE DADOS ---------------------------- //
typedef enum CANDY_TYPE 
{
    CT_RED = 0,
    CT_PURPLE,
    CT_GREEN,
    CT_ORANGE,
    CT_BLUE,
    CT_BROWN,
    CT_GRAY,
    CT_BLACK,
    CANDY_TYPE_N
} CANDY_TYPE;

typedef struct CANDY
{
    int x, y;
    int xBoardPos, yBoardPos;
    CANDY_TYPE type;
    bool moving;
    bool match;
} CANDY;

typedef struct BOARD 
{
    int score;
    CANDY *grid[BOARD_ROW][BOARD_COL];
} BOARD;

// ---------------------------- VARIAVEIS GLOBAIS ------------------------- //
extern BOARD               *board;
extern unsigned char       key[ALLEGRO_KEY_MAX];

// -------------- ALLEGRO ------------- //
extern ALLEGRO_DISPLAY     *display;
extern ALLEGRO_BITMAP      *sprites[19];
extern ALLEGRO_TIMER       *timer;
extern ALLEGRO_EVENT_QUEUE *queue;
extern ALLEGRO_SAMPLE *sample_bg;
extern ALLEGRO_SAMPLE *sample_mult[5];
extern ALLEGRO_SAMPLE *sample_clear;
extern ALLEGRO_SAMPLE *sample_wrong_play;

// ----------------------------- FUNCOES ---------------------------------- //
// Retorna um inteiro aleatorio entre lo e hi
void must_init(bool test, const char *description);
ALLEGRO_BITMAP *sprite_grab(int x, int y, int w, int h, ALLEGRO_BITMAP *spriteSheet);
bool within(int top, int bottom, int x);
int aleat(int lo, int hi);


#endif
