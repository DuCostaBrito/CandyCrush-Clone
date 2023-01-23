#include "candy.h"

int between(int lo, int hi)
{
    return lo + (rand() % (hi - lo));
}



void initializeBoard(CANDY board[8][8], int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            // Escolhe um tipo aleatorio
            enum CANDY_TYPE ct = (between(0, CANDY_TYPE_N));
            board[i][j].type = ct;
            board[i][j].xBoardPos = i;
            board[i][j].yBoardPos = j;
            board[i][j].x = 56 + ((j + 1) * 20) + ((j + 1) * 40);
            board[i][j].y = 55 + ((i + 1) * 35) + ((i + 1) * 40);
            board[i][j].seq = false;
        }
    }
    return;
}