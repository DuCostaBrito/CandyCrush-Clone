#ifndef _candy_t_H
#define _candy_t_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


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
    int r;
} CANDY;

void initializeBoard(CANDY board[9][5]);

#endif