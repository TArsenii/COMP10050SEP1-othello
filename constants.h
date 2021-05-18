#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED


#define N 8
#define MAXSTR 100

// global variable that simplifies
// iterating over all the possible directions
// (contains pairs of a form dx, dy)
int DIRECTIONS[8][2];

// constants
// used to denote the player to move
// and to denote disc positions on the board
enum square_t
{
    EMPTY,
    BLACK,
    WHITE
};

#endif // CONSTANTS_H_INCLUDED
