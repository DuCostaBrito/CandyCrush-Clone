#include "candy.h"

int between(int lo, int hi)
{
    return lo + (rand() % (hi - lo));
}



void initializeBoard(CANDY board[9][5]) {
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 5; j++) {
            // Escolhe um tipo aleatorio
            enum CANDY_TYPE ct = (between(0, CANDY_TYPE_N));
            board[i][j].type = ct;
            board[i][j].xBoardPos = i;
            board[i][j].yBoardPos = j;
            board[i][j].x = 50 + 24 + ((j + 1) * 35) + (j * 54);
            board[i][j].y = 150 + 45 + ((i + 1) * 35) + (i * 50);
        }
    }
    return;
}