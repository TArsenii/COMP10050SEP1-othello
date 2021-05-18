#include "board.h"

int DIRECTIONS[8][2] =
{
    { -1, -1},
    { -1, 0},
    { -1, +1},

    { 0, -1},
    { 0, +1},


    { 1, -1},
    { 1, 0},
    { 1, +1},

};


char * const get_color_name(enum square_t to_move)
{
    switch(to_move)
    {
    case BLACK:
        return "Black";
    case WHITE:
        return "White";
    default:
        return "";
    }
}


// https://stackoverflow.com/questions/5141960/get-the-current-time-in-c
void init_board(struct board_t *pb)
{
    for (int i = 0; i != N; ++i)
        for (int j = 0; j != N; ++j)
            pb->board[i][j] = EMPTY;

    pb->board[3][3] = WHITE;
    pb->board[3][4] = BLACK;
    pb->board[4][4] = WHITE;
    pb->board[4][3] = BLACK;

    pb->to_move = BLACK;
}



int valid(int r, int c)
{
    return r >= 0 && c >= 0 && r <= 7 && c <= 7;
}
