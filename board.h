#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "constants.h"

// board class
// stores the board state
// this information is enough to continue the game
// according to the rules
struct board_t
{
    enum square_t board[N][N];
    int to_move;
};

// simplifies printing of the color names
char * const get_color_name(enum square_t to_move);

// sets up the initial board state
void init_board(struct board_t *pb);

// checks whether the coordinates (0-7, 0-7) are in
// the valid range
int valid(int r, int c);

#endif // BOARD_H_INCLUDED
