#ifndef _candy_t_H
#define _candy_t_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <math.h>

//Definindo cores
#define PIXEL(r,g,b) (al_map_rgb((unsigned char) r, (unsigned char) g, (unsigned char) b))
#define RED PIXEL(220, 20, 60)
#define PURPLE PIXEL(238, 130, 238)
#define GREEN PIXEL(144, 238, 144)
#define ORANGE PIXEL(255, 222, 173)
#define BLUE PIXEL(135, 206, 250)
#define BROWN PIXEL(139, 87, 66)
#define GRAY PIXEL(211, 211, 211)
#define BLACK PIXEL(0,0,0)



#define BOARD_ROW 9
#define BOARD_COL 5
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

BOARD *createBoard();
void drawBoard(BOARD *board, ALLEGRO_BITMAP *sprites[19]);
void swipeColors(BOARD *board, int srcIndexX, int srcIndexY, int destIndexX, int destIndexY, ALLEGRO_BITMAP *sprites[19]);
bool verifyMatch(BOARD *board);
void fallBoard(BOARD *board, ALLEGRO_BITMAP *sprites[19]);
bool isEmpty(BOARD *board);
void  fillBoard(BOARD *board, ALLEGRO_BITMAP *sprites[19]);
void showScore(ALLEGRO_BITMAP *numbers[10], BOARD *board);

#endif