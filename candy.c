#include "candy.h"

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

void shuffleBoard(BOARD *board)
{
    for (int i = 0; i < BOARD_ROW; i++)
    {
        for (int j = 0; j < BOARD_COL; j++)
        {
            board->grid[i][j]->type = aleat(0, CANDY_TYPE_N);
        }
    }
    board->score = 0;
    return;
}

void drawCandy(CANDY *candy, int x, int y, ALLEGRO_BITMAP *sprites[19])
{
    if (candy->match)
        return;
    switch (candy->type)
    {
    case CT_RED:
        al_draw_bitmap(sprites[10], x, y, 0);
        break;
    case CT_PURPLE:
        al_draw_bitmap(sprites[11], x, y, 0);
        break;
    case CT_GREEN:
        al_draw_bitmap(sprites[12], x, y, 0);
    case CT_ORANGE:
        al_draw_bitmap(sprites[13], x, y, 0);
        break;
    case CT_BLUE:
        al_draw_bitmap(sprites[14], x, y, 0);
        break;
    case CT_BROWN:
        al_draw_bitmap(sprites[15], x, y, 0);
        break;
    case CT_GRAY:
        al_draw_bitmap(sprites[16], x, y, 0);
        break;
    case CT_BLACK:
        al_draw_bitmap(sprites[17], x, y, 0);
        break;
    }
}

void drawBoard(BOARD *board, ALLEGRO_BITMAP *sprites[19])
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

void swipeColors(BOARD *board, int srcIndexX, int srcIndexY, int destIndexX, int destIndexY, ALLEGRO_BITMAP *sprites[19])
{
    int count = 2;
    enum CANDY_TYPE aux = board->grid[srcIndexX][srcIndexY]->type;
    board->grid[srcIndexX][srcIndexY]->moving = true;
    board->grid[destIndexX][destIndexY]->moving = true;
    if (srcIndexY < destIndexY)
    {
        // right
        while (board->grid[srcIndexX][srcIndexY]->x + count < board->grid[destIndexX][destIndexY]->x)
        {
            al_draw_bitmap(sprites[18], 0, 0, 0);
            drawCandy(board->grid[srcIndexX][srcIndexY], board->grid[srcIndexX][srcIndexY]->x + count, board->grid[srcIndexX][srcIndexY]->y, sprites);
            drawCandy(board->grid[destIndexX][destIndexY], board->grid[destIndexX][destIndexY]->x - count, board->grid[destIndexX][destIndexY]->y, sprites);
            drawBoard(board, sprites);
            drawSetting();
            showScore(board);
            al_flip_display();
            count += 6;
        }
    }
    else if (srcIndexX < destIndexX)
    {
        // down
        while (board->grid[srcIndexX][srcIndexY]->y + count < board->grid[destIndexX][destIndexY]->y)
        {
            al_draw_bitmap(sprites[18], 0, 0, 0);
            drawCandy(board->grid[srcIndexX][srcIndexY], board->grid[srcIndexX][srcIndexY]->x, board->grid[srcIndexX][srcIndexY]->y + count, sprites);
            drawCandy(board->grid[destIndexX][destIndexY], board->grid[destIndexX][destIndexY]->x, board->grid[destIndexX][destIndexY]->y - count, sprites);
            drawBoard(board, sprites);
            drawSetting();
            showScore(board);
            al_flip_display();
            count += 6;
        }
    }
    else if (srcIndexY > destIndexY)
    {
        // left
        while (board->grid[srcIndexX][srcIndexY]->x - count > board->grid[destIndexX][destIndexY]->x)
        {
            al_draw_bitmap(sprites[18], 0, 0, 0);
            drawCandy(board->grid[srcIndexX][srcIndexY], board->grid[srcIndexX][srcIndexY]->x - count, board->grid[srcIndexX][srcIndexY]->y, sprites);
            drawCandy(board->grid[destIndexX][destIndexY], board->grid[destIndexX][destIndexY]->x + count, board->grid[destIndexX][destIndexY]->y, sprites);
            drawBoard(board, sprites);
            drawSetting();
            showScore(board);
            al_flip_display();
            count += 6;
        }
    }
    else if (srcIndexX > destIndexX)
    {
        // up
        while (board->grid[srcIndexX][srcIndexY]->y - count > board->grid[destIndexX][destIndexY]->y)
        {
            al_draw_bitmap(sprites[18], 0, 0, 0);
            drawCandy(board->grid[srcIndexX][srcIndexY], board->grid[srcIndexX][srcIndexY]->x, board->grid[srcIndexX][srcIndexY]->y - count, sprites);
            drawCandy(board->grid[destIndexX][destIndexY], board->grid[destIndexX][destIndexY]->x, board->grid[destIndexX][destIndexY]->y + count, sprites);
            drawBoard(board, sprites);
            drawSetting();
            showScore(board);
            al_flip_display();
            count += 6;
        }
    }
    board->grid[srcIndexX][srcIndexY]->moving = false;
    board->grid[destIndexX][destIndexY]->moving = false;
    board->grid[srcIndexX][srcIndexY]->type = board->grid[destIndexX][destIndexY]->type;
    board->grid[destIndexX][destIndexY]->type = aux;
    return;
}

void showMult(int mult)
{
    int count;
    for (count = 0; count < 40; count++)
    {
        al_draw_bitmap(sprites[18], 0, 0, 0);
        drawBoard(board, sprites);
        showScore(board);
        drawSetting();
        al_draw_bitmap(sprites[mult], 180 + count, 100 - count, 0);
        al_flip_display();
    }
    return;
}

bool isPossible(BOARD *board)
{
    int i, j;
    // verifica horizontal
    for (i = 0; i < BOARD_ROW; i++)
        for (j = 0; j < BOARD_COL - 2; j++)
        {
            if (i == 0)
            {
                if (board->grid[i][j]->type == board->grid[i][j + 2]->type && board->grid[i + 1][j + 1]->type == board->grid[i][j]->type)
                    return true;
                else if (board->grid[i][j]->type == board->grid[i][j + 1]->type && board->grid[i + 1][j + 2]->type == board->grid[i][j]->type)
                    return true;
                else if (board->grid[i][j]->type == board->grid[i + 1][j + 2]->type && board->grid[i + 1][j + 1]->type == board->grid[i][j]->type)
                    return true;
            }
            else if (i == BOARD_ROW - 1)
            {
                if (board->grid[i][j]->type == board->grid[i][j + 2]->type && board->grid[i - 1][j + 1]->type == board->grid[i][j]->type)
                    return true;
                else if (board->grid[i][j]->type == board->grid[i][j + 1]->type && board->grid[i - 1][j + 2]->type == board->grid[i][j]->type)
                    return true;
                else if (board->grid[i][j]->type == board->grid[i - 1][j + 1]->type && board->grid[i - 1][j + 2]->type == board->grid[i][j]->type)
                    return true;
            }
            else if ((board->grid[i][j]->type == board->grid[i][j + 2]->type) && (board->grid[i + 1][j + 1]->type == board->grid[i][j]->type || board->grid[i - 1][j + 1]->type == board->grid[i][j]->type))
                return true;
            else if ((board->grid[i][j]->type == board->grid[i][j + 1]->type) && (board->grid[i + 1][j + 2]->type == board->grid[i][j]->type || board->grid[i - 1][j + 2]->type == board->grid[i][j]->type))
                return true;
            else if (board->grid[i][j]->type == board->grid[i - 1][j + 1]->type && board->grid[i - 1][j + 2]->type == board->grid[i][j]->type)
                return true;
            else if (board->grid[i][j]->type == board->grid[i + 1][j + 2]->type && board->grid[i + 1][j + 1]->type == board->grid[i][j]->type)
                return true;
            if (j < BOARD_COL - 3)
                if (board->grid[i][j]->type == board->grid[i][j + 1]->type && board->grid[i][j]->type == board->grid[i][j + 3]->type)
                    return true;
        }
    // verifica vertical
    for (i = 0; i < BOARD_ROW - 2; i++)
        for (j = 0; j < BOARD_COL; j++)
        {
            if (j == 0)
            {
                if (board->grid[i][j]->type == board->grid[i + 2][j]->type && board->grid[i + 1][j + 1]->type == board->grid[i][j]->type)
                    return true;
                else if (board->grid[i][j]->type == board->grid[i + 1][j]->type && board->grid[i + 2][j + 1]->type == board->grid[i][j]->type)
                    return true;
                else if (board->grid[i][j]->type == board->grid[i + 1][j + 1]->type && board->grid[i + 2][j + 1]->type == board->grid[i][j]->type)
                    return true;
            }
            else if (j == BOARD_COL - 1)
            {
                if (board->grid[i][j]->type == board->grid[i + 2][j]->type && board->grid[i + 1][j - 1]->type == board->grid[i][j]->type)
                    return true;
                else if (board->grid[i][j]->type == board->grid[i + 1][j]->type && board->grid[i + 2][j - 1]->type == board->grid[i][j]->type)
                    return true;
                else if (board->grid[i][j]->type == board->grid[i + 1][j - 1]->type && board->grid[i + 2][j - 1]->type == board->grid[i][j]->type)
                    return true;
            }
            else if ((board->grid[i][j]->type == board->grid[i + 2][j]->type) && (board->grid[i + 1][j + 1]->type == board->grid[i][j]->type || board->grid[i + 1][j - 1]->type == board->grid[i][j]->type))
                return true;
            else if ((board->grid[i][j]->type == board->grid[i + 1][j]->type) && (board->grid[i + 2][j + 1]->type == board->grid[i][j]->type || board->grid[i + 2][j - 1]->type == board->grid[i][j]->type))
                return true;
            else if (board->grid[i][j]->type == board->grid[i + 1][j - 1]->type && board->grid[i + 2][j - 1]->type == board->grid[i][j]->type)
                return true;
            else if (board->grid[i][j]->type == board->grid[i + 1][j + 1]->type && board->grid[i + 2][j + 1]->type == board->grid[i][j]->type)
                return true;
            if (i < BOARD_ROW - 3)
                if (board->grid[i][j]->type == board->grid[i + 1][j]->type && board->grid[i][j]->type == board->grid[i + 3][j]->type)
                    return true;
        }
    return false;
}

bool verifyMatch(BOARD *board, int mult)
{
    int i, j;
    int count;
    enum CANDY_TYPE ct;
    for (i = 0; i < BOARD_ROW; i++)
        for (j = 0; j < BOARD_COL; j++)
        {
            count = 1;
            if (!board->grid[i][j]->match)
            {
                while ((j + count < BOARD_COL) && (board->grid[i][j]->type == board->grid[i][j + count]->type) && (!board->grid[i][j + count]->match))
                {
                    count++;
                }
                if (count >= 3)
                {
                    board->score = board->score + ((mult + 1) * count * 100);
                    count--;
                    for (count; count >= 0; count--)
                    {
                        board->grid[i][j + count]->match = true;
                    }
                    showMult(mult + 1);
                    if (sound_on)
                        al_play_sample(sample_mult[mult], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    return true;
                }
                count = 1;
                while ((i + count < BOARD_ROW) && (board->grid[i][j]->type == board->grid[i + count][j]->type) && (!board->grid[i + count][j]->match))
                {
                    count++;
                }
                if (count >= 3)
                {
                    board->score = board->score + ((mult + 1) * count * 100);
                    count--;
                    for (count; count >= 0; count--)
                    {
                        board->grid[i  + count][j]->match = true;
                    }
                    showMult(mult + 1);
                    if (sound_on)
                        al_play_sample(sample_mult[mult], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    return true;
                }
            }
            
        }
    return false;
}

void fallBoard(BOARD *board, ALLEGRO_BITMAP *sprites[N_SPRITES])
{
    int i, j;
    int c = 1;
    for (i = BOARD_ROW - 1; i > 0; i--)
        for (j = BOARD_COL - 1; j >= 0; j--)
        {
            if (board->grid[i][j]->match)
            {
                while (board->grid[i - c][j]->match)
                {
                    if (i - c <= 0)
                        return;
                    c++;
                }
                swipeColors(board, i, j, i - c, j, sprites);
                board->grid[i][j]->match = false;
                board->grid[i - c][j]->match = true;
                c = 1;
            }
        }
    return;
}

bool isEmpty(BOARD *board)
{
    int i, j;
    for (i = 0; i < BOARD_ROW; i++)
        for (j = 0; j < BOARD_COL; j++)
        {
            if (board->grid[i][j]->match)
                return true;
        }
    return false;
}

void fillBoard(BOARD *board, ALLEGRO_BITMAP *sprites[N_SPRITES])
{

    for (int j = 0; j < BOARD_COL; j++)
    {
        if (board->grid[0][j]->match)
        {
            board->grid[0][j]->type = aleat(0, CANDY_TYPE_N);
            board->grid[0][j]->match = false;
        }
    }
    fallBoard(board, sprites);
    return;
}

void showScore(BOARD *board)
{
    int total, uni, dez, cen, mil, dez_mil, cem_mil;
    total = board->score;
    uni = total % 10;
    total = floor(total / 10);
    dez = total % 10;
    total = floor(total / 10);
    cen = total % 10;
    total = floor(total / 10);
    mil = total % 10;
    total = floor(total / 10);
    dez_mil = total % 10;
    total = floor(total / 10);
    cem_mil = total;

    al_draw_bitmap(sprites[cem_mil], 26, 80, 0);
    al_draw_bitmap(sprites[dez_mil], 56, 80, 0);
    al_draw_bitmap(sprites[mil], 86, 80, 0);
    al_draw_bitmap(sprites[cen], 116, 80, 0);
    al_draw_bitmap(sprites[dez], 146, 80, 0);
    al_draw_bitmap(sprites[uni], 176, 80, 0);
    return;
}

void checkRecord(int score)
{
    int aux;
    FILE *file = fopen(".recorde", "r+");
    fscanf(file, "%d", &aux);
    if (score > aux || score > 20000)
    {
        fseek(file, 0, SEEK_SET);
        fprintf(file, "%d", score);
    }
    fclose(file);
    return;
}

void showRecord()
{
    FILE *file = fopen(".recorde", "r");
    int total, uni, dez, cem, mil, dez_mil, cem_mil;
    fscanf(file, "%d", &total);
    uni = total % 10;
    total = floor(total / 10);
    dez = total % 10;
    total = floor(total / 10);
    cem = total % 10;
    total = floor(total / 10);
    mil = total % 10;
    total = floor(total / 10);
    dez_mil = total % 10;
    total = floor(total / 10);
    cem_mil = total;

    al_draw_bitmap(sprites[cem_mil], WIDTH / 2 - 93, HEIGHT / 2 + 10, 0);
    al_draw_bitmap(sprites[dez_mil], WIDTH / 2 - 63, HEIGHT / 2 + 10, 0);
    al_draw_bitmap(sprites[mil], WIDTH / 2 - 33, HEIGHT / 2 + 10, 0);
    al_draw_bitmap(sprites[cem], WIDTH / 2 - 3, HEIGHT / 2 + 10, 0);
    al_draw_bitmap(sprites[dez], WIDTH / 2 + 27, HEIGHT / 2 + 10, 0);
    al_draw_bitmap(sprites[uni], WIDTH / 2 + 57, HEIGHT / 2 + 10, 0);

    fclose(file);
}

void freeBoard()
{
    for (int i = 0; i < BOARD_ROW; i++)
        for (int j = 0; j < BOARD_COL; j++)
            free(board->grid[i][j]);
    free(board);
}