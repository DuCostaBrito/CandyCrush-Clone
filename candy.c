#include "candy.h"

int aleat(int lo, int hi)
{
    return lo + (rand() % (hi - lo));
}

CANDY *createCandy()
{
    CANDY *candy = malloc(sizeof(CANDY));
    if (!candy)
        return NULL;
    enum CANDY_TYPE ct = (aleat(0, CANDY_TYPE_N));
    candy->match = false;
    candy->rightPosition = false;
    candy->type = ct;
    candy->x = 0;
    candy->y = 0;
    candy->xBoardPos = 0;
    candy->yBoardPos = 0;
    return candy;
}

BOARD *createBoard()
{
    BOARD *board = malloc(sizeof(BOARD));
    if (!board)
        return NULL;
    int i, j;
    board->score = 0;
    for (i = 0; i < BOARD_ROW; i++)
    {
        for (j = 0; j < BOARD_COL; j++)
        {
            board->grid[i][j] = createCandy();
            board->grid[i][j]->xBoardPos = i;
            board->grid[i][j]->yBoardPos = j;
            board->grid[i][j]->x = 50 + 24 + ((j + 1) * 35) + (j * 54);
            board->grid[i][j]->y = 150 + 45 + ((i + 1) * 35) + (i * 50);
        }
    }
    return board;
}

void drawBoard(BOARD *board)
{
    for (int i = 0; i < BOARD_ROW; i++)
    {
        for (int j = 0; j < BOARD_COL; j++)
        {
            switch (board->grid[i][j]->type)
            {
            case CT_RED:
                al_draw_filled_circle(board->grid[i][j]->x, board->grid[i][j]->y, 35, RED);
                break;
            case CT_PURPLE:
                al_draw_filled_circle(board->grid[i][j]->x, board->grid[i][j]->y, 35, PURPLE);
                break;
            case CT_GREEN:
                al_draw_filled_circle(board->grid[i][j]->x, board->grid[i][j]->y, 35, GREEN);
            case CT_ORANGE:
                al_draw_filled_circle(board->grid[i][j]->x, board->grid[i][j]->y, 35, ORANGE);
                break;
            case CT_BLUE:
                al_draw_filled_circle(board->grid[i][j]->x, board->grid[i][j]->y, 35, BLUE);
                break;
            case CT_BROWN:
                al_draw_filled_circle(board->grid[i][j]->x, board->grid[i][j]->y, 35, BROWN);
                break;
            case CT_GRAY:
                al_draw_filled_circle(board->grid[i][j]->x, board->grid[i][j]->y, 35, GRAY);
                break;
            case CT_BLACK:
                al_draw_filled_circle(board->grid[i][j]->x, board->grid[i][j]->y, 35, BLACK);
                break;

            default:
                break;
            }
            al_draw_circle(board->grid[i][j]->x, board->grid[i][j]->y, 35, al_map_rgb(255, 255, 255), 2);
        }
    }
}

void changeColors(BOARD *board, int srcIndexX, int srcIndexY, int destIndexX, int destIndexY)
{
    enum CANDY_TYPE aux;
    aux = board->grid[srcIndexX][srcIndexY]->type;
    board->grid[srcIndexX][srcIndexY]->type = board->grid[destIndexX][destIndexY]->type;
    board->grid[destIndexX][destIndexY]->type = aux;
}