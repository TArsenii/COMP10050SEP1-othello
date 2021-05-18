#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "constants.h"
#include "board.h"
#include "game.h"

// print the board lines horizontal separator
void print_h_separator()
{

    for (int i = 0; i != 4; ++i)
        printf(" ");

    for (int j = 0; j != N; ++j)
    {
        printf("--- ");
    }
    puts("");

}

// print a row of the board
// including highlighting the possible moves
// and the discs in play
void print_row(int i, struct game_t * const pg)
{
    printf("%-3d|", i + 1);

    for (int j = 0; j != N; ++j)
    {
        switch (pg->board.board[i][j])
        {
        case BLACK:
            printf("%s", " B ");
            break;
        case WHITE:
            printf("%s", " W ");
            break;
        default:
            if (pg->highlights[i][j])
                printf("%s", " o ");
            else
                printf("%s", "   ");
            break;
        }

        printf("|");
    }
    puts("");
}


// prints the game after each move
void print_game(struct game_t * const pg)
{

    printf("Score: %s (Black) %d:%d %s (White)\n",
           pg->p1,
           pg->p1score, pg->p2score,
           pg->p2);
    print_h_separator();
    for (int i = 0; i != N; ++i)
    {
        print_row(i, pg);
        print_h_separator();
    }

    for (int i = 0; i != 4; ++i)
        printf(" ");

    for (int j = 0; j != N; ++j)
    {
        printf(" %c  ", 'a' + j);
    }
    puts("");
}

int main()
{
    struct game_t game;

    puts("*** Welcome to Othello! ***\n");
    init_game(&game);

    while (1)
    {
        print_game(&game);
        char buf[MAXSTR];
        printf("Player %s to move (%d possible moves): ",
               get_color_name(game.board.to_move),
               game.highlights_count);
        fgets(buf, MAXSTR, stdin);
        buf[strlen(buf) - 1] = 0;

        if (strcmp(buf, "p") == 0)
        {
            if (game.highlights_count != 0) {
                puts("there are some possible moves, you can't pass the move");
            } else {
                puts("pass");
                ++game.pass_count;

                if (game.pass_count == 2) {
                    puts("2 passes in a row, the game is over!");
                    break;
                }

                game.board.to_move = game.board.to_move == BLACK ? WHITE : BLACK;

            }
        }
        else if (strcmp(buf, "q") == 0)
        {
            puts("bye");
            exit(1);
        }
        else
        {
            if (strlen(buf) != 2
                    || buf[0] < 'a' || buf[0] > 'h'
                    || buf[1] < '1' || buf[1] > '8')
            {
                puts("wrong square, please try again\n");
                continue;
            }

            int r = buf[1] - '1';
            int c = buf[0] - 'a';

            // available move should be highlighted
            if (!game.highlights[r][c])
            {
                puts("not a valid move, please try again\n");
                continue;
            }

            // effectuate the move
            // puts("good move");

            int to_move, other;
            if (game.board.to_move == BLACK)
            {
                to_move = BLACK;
                other = WHITE;
            }
            else
            {
                to_move = WHITE;
                other = BLACK;
            }

            // need to reverse in all the
            // affected directions
            for (int k = 0; k != 8; ++k)
                if (test_dir(&game,
                             r, c,
                             DIRECTIONS[k][0],
                             DIRECTIONS[k][1],
                             to_move, other))
                {
                    reverse(&game,
                            r, c,
                            DIRECTIONS[k][0],
                            DIRECTIONS[k][1],
                            to_move, other);
                }

            game.board.board[r][c] = to_move;
            game.board.to_move = other;

            game.pass_count = 0;

            update_score(&game);
            highlight(&game);
        }
    }

    puts("game over!");
    if (game.p1score > game.p2score)
        printf("%s won!\n", game.p1);
    else if (game.p1score < game.p2score)
        printf("%s won!\n", game.p2);
    else
        printf("draw!\n");

    print_game(&game);

    FILE *output_file = fopen("othello-results.txt", "a");
    fprintf(output_file, "%s\n", game.date);

    if (game.p1score > game.p2score)
        fprintf(output_file, "%s won!\n", game.p1);
    else if (game.p1score < game.p2score)
        fprintf(output_file, "%s won!\n", game.p2);
    else
        fprintf(output_file, "draw!\n");

    fprintf(output_file, "Score: %s (Black) %d:%d %s (White)\n",
            game.p1,
            game.p1score, game.p2score,
            game.p2);

    fclose(output_file);


    return 0;
}
