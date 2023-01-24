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
    candy->moving = false;
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
            board->grid[i][j]->x = 50 + 24 + (j * 90);
            board->grid[i][j]->y = 150 + 45 + (i * 85);
        }
    }
    return board;
}

void drawCandy(CANDY *candy, int x, int y, ALLEGRO_BITMAP *sprites[8])
{
    switch (candy->type)
    {
    case CT_RED:
        al_draw_bitmap(sprites[0], x, y, 0);
        break;
    case CT_PURPLE:
        al_draw_bitmap(sprites[1], x, y, 0);
        break;
    case CT_GREEN:
        al_draw_bitmap(sprites[2], x, y, 0);
    case CT_ORANGE:
        al_draw_bitmap(sprites[3], x, y, 0);
        break;
    case CT_BLUE:
        al_draw_bitmap(sprites[4], x, y, 0);
        break;
    case CT_BROWN:
        al_draw_bitmap(sprites[5], x, y, 0);
        break;
    case CT_GRAY:
        al_draw_bitmap(sprites[6], x, y, 0);
        break;
    case CT_BLACK:
        al_draw_bitmap(sprites[7], x, y, 0);
        break;

    default:
        break;
    }
}

void drawBoard(BOARD *board, ALLEGRO_BITMAP *sprites[8])
{
    for (int i = 0; i < BOARD_ROW; i++)
    {
        for (int j = 0; j < BOARD_COL; j++)
        {
            if (!board->grid[i][j]->moving)
                drawCandy(board->grid[i][j], board->grid[i][j]->x, board->grid[i][j]->y, sprites);
        }
    }
}

void changeColors(BOARD *board, int srcIndexX, int srcIndexY, int destIndexX, int destIndexY, ALLEGRO_BITMAP *bg, ALLEGRO_BITMAP *sprites[8])
{
    int count = 2;
    enum CANDY_TYPE aux = board->grid[srcIndexX][srcIndexY]->type;
    board->grid[srcIndexX][srcIndexY]->moving = true;
    board->grid[destIndexX][destIndexY]->moving = true;
    if (srcIndexY < destIndexY)
    {
        //right
        while (board->grid[srcIndexX][srcIndexY]->x + count < board->grid[destIndexX][destIndexY]->x)
        {
            al_draw_bitmap(bg, 0,0,0);
            drawCandy(board->grid[srcIndexX][srcIndexY], board->grid[srcIndexX][srcIndexY]->x + count, board->grid[srcIndexX][srcIndexY]->y, sprites);
            drawCandy(board->grid[destIndexX][destIndexY], board->grid[destIndexX][destIndexY]->x - count, board->grid[destIndexX][destIndexY]->y, sprites);
            drawBoard(board, sprites);
            al_flip_display();
            count += 4;
        }
    }
    else if (srcIndexX < destIndexX)
    {
        //down
        while (board->grid[srcIndexX][srcIndexY]->y + count < board->grid[destIndexX][destIndexY]->y)
        {
            al_draw_bitmap(bg, 0,0,0);
            drawCandy(board->grid[srcIndexX][srcIndexY], board->grid[srcIndexX][srcIndexY]->x, board->grid[srcIndexX][srcIndexY]->y + count, sprites);
            drawCandy(board->grid[destIndexX][destIndexY], board->grid[destIndexX][destIndexY]->x, board->grid[destIndexX][destIndexY]->y - count, sprites);
            drawBoard(board, sprites);
            al_flip_display();
            count += 4;
        }
    }
    else if (srcIndexY > destIndexY)
    {
        //left
        while (board->grid[srcIndexX][srcIndexY]->x - count > board->grid[destIndexX][destIndexY]->x)
        {
            al_draw_bitmap(bg, 0,0,0);
            drawCandy(board->grid[srcIndexX][srcIndexY], board->grid[srcIndexX][srcIndexY]->x - count, board->grid[srcIndexX][srcIndexY]->y, sprites);
            drawCandy(board->grid[destIndexX][destIndexY], board->grid[destIndexX][destIndexY]->x + count, board->grid[destIndexX][destIndexY]->y, sprites);
            drawBoard(board, sprites);
            al_flip_display();
            count += 4;
        }
    }
    else if (srcIndexX > destIndexX)
    {
        //up
        while (board->grid[srcIndexX][srcIndexY]->y - count > board->grid[destIndexX][destIndexY]->y)
        {
            al_draw_bitmap(bg, 0,0,0);
            drawCandy(board->grid[srcIndexX][srcIndexY], board->grid[srcIndexX][srcIndexY]->x, board->grid[srcIndexX][srcIndexY]->y - count, sprites);
            drawCandy(board->grid[destIndexX][destIndexY], board->grid[destIndexX][destIndexY]->x, board->grid[destIndexX][destIndexY]->y + count, sprites);
            drawBoard(board, sprites);
            al_flip_display();
            count += 4;
        }
    }
    board->grid[srcIndexX][srcIndexY]->moving = false;
    board->grid[destIndexX][destIndexY]->moving = false;
    board->grid[srcIndexX][srcIndexY]->type = board->grid[destIndexX][destIndexY]->type;
    board->grid[destIndexX][destIndexY]->type = aux;
    return;
}