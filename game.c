#include <stdio.h>
#include <string.h>
#include <time.h>

#include "game.h"

void init_game(struct game_t *pg)
{
    printf("player 1 (Black): ");
    fgets(pg->p1, MAXSTR, stdin);
    pg->p1[strlen(pg->p1) - 1] = 0;
    printf("player 2 (Black): ");
    fgets(pg->p2, MAXSTR, stdin);
    pg->p2[strlen(pg->p2) - 1] = 0;

    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strcpy(pg->date, asctime(timeinfo));

    init_board(&pg->board);
    update_score(pg);

    highlight(pg);
    pg->pass_count = 0;
}



void update_score(struct game_t *pg)
{
    pg->p1score = 0;
    pg->p2score = 0;
    for (int i = 0; i != N; ++i)
        for (int j = 0; j != N; ++j)
        {
            if (pg->board.board[i][j] == BLACK)
                ++pg->p1score;
            else if (pg->board.board[i][j] == WHITE)
                ++pg->p2score;
        }
}



void highlight(struct game_t * pg)
{
    for (int i = 0; i != N; ++i)
        for (int j = 0; j != N; ++j)
            pg->highlights[i][j] = 0;

    int to_move, other;
    if (pg->board.to_move == BLACK)
    {
        to_move = BLACK;
        other = WHITE;
    }
    else
    {
        to_move = WHITE;
        other = BLACK;
    }

    pg->highlights_count = 0;
    for (int i = 0; i != N; ++i)
        for (int j = 0; j != N; ++j)
        {
            if (pg->board.board[i][j] != EMPTY)
                continue;

            for (int k = 0; k != 8; ++k)
                if (test_dir(pg,
                             i, j,
                             DIRECTIONS[k][0],
                             DIRECTIONS[k][1],
                             to_move, other)) {
                    pg->highlights[i][j] = 1;
                    ++pg->highlights_count;
                    break;
                }
        }


    //  highlights[0][1] = 1;
    //highlights[7][7] = 1;

}


int test_dir(struct game_t * const pg,
             int r, int c, int dr, int dc,
             int to_move, int other)
{
    int i = r + dr;
    int j = c + dc;

    // if the next square in the given direction
    // is out of the board, the move is fault immediately
    if (!valid(i, j))
        return 0;

    // there must be at least one stone
    // of the other colour
    if (pg->board.board[i][j] != other)
        return 0;

    // there can be any # of stones to be reversed (>=1)
    i += dr;
    j += dc;

    while (valid(i, j)
            && pg->board.board[i][j] == other)
    {
        i += dr;
        j += dc;
    }

    // after a string of the stones of the opposite
    // colour, there should be the stone
    // of the to_move colour
    if (!valid(i, j))
        return 0;

    if (pg->board.board[i][j] != to_move)
        return 0;

    return 1;
}



void reverse(struct game_t * const pg,
             int r, int c, int dr, int dc,
             int to_move, int other)
{

    int i = r + dr;
    int j = c + dc;
    while (pg->board.board[i][j] != to_move)
    {
        pg->board.board[i][j] = to_move;
        i += dr;
        j += dc;
    }
}

