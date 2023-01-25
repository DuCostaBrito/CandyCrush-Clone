#ifndef _candy_t_H
#define _candy_t_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <math.h>
#include "global.h"
#include "menu.h"

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

BOARD *createBoard();
void drawBoard(BOARD *board, ALLEGRO_BITMAP *sprites[N_SPRITES]);
void swipeColors(BOARD *board, int srcIndexX, int srcIndexY, int destIndexX, int destIndexY, ALLEGRO_BITMAP *sprites[19]);
bool verifyMatch(BOARD *board, int mult);
void fallBoard(BOARD *board, ALLEGRO_BITMAP *sprites[N_SPRITES]);
bool isEmpty(BOARD *board);
void  fillBoard(BOARD *board, ALLEGRO_BITMAP *sprites[N_SPRITES]);
void showScore(ALLEGRO_BITMAP *numbers[10], BOARD *board);
void shuffleBoard(BOARD *board);

#endif