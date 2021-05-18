#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "board.h"

// contains the current game state
// including the board
struct game_t
{
    // player names
    char p1[MAXSTR];
    char p2[MAXSTR];

    // current date
    // (initialized in the beginning of the game)
    char date[MAXSTR];

    struct board_t board;

    // the following 4 variables are recalculated
    // after each move

    // auxiliary array that is used to
    // highlight possible moves
    int highlights[N][N];

    // # of moves available
    int highlights_count;

    int p1score, p2score;

    // # of continuous passes
    // the game finishes when this counter becomes 2
    int pass_count;
};


// actualize available moves array &
// their count
void highlight(struct game_t * const pg);

// recounts # of discs
void update_score(struct game_t *pg);

// initializes the game
// including player names
void init_game(struct game_t *pg);

// test whether a move is possible
// r, c = square where the disc is placed
// in a given direction (dr, dc)
int test_dir(struct game_t * const pg,
             int r, int c, int dr, int dc,
             int to_move, int other);

// reverses squares after a move has been made
// r, c = square where the disc is placed
// in a given direction (dr, dc)
void reverse(struct game_t * const pg,
             int r, int c, int dr, int dc,
             int to_move, int other);

#endif // GAME_H_INCLUDED
