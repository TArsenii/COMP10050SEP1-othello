# COMP10050SEP1-othello
COMP10050 Software Engineering Project 1 - Othello Game

# design 

At first I analyzed which information is necessary to represent a state of a particular game
in each moment. The game state is completely determined by the position of stones on the board
and the move order.
This information is encapsulated in the board_t class.

In order to store the auxiliary game information (player names, date) I added the game class, which
also encapsulates the current state of the board.

I used eothello.com website to try the game & understand the rules better, and I decided to implement 
the square highlighting because it provided me with more opportunities to compare the squares
highlighted on the website & in my program, besides being a useful user interface feature.

The important part was to write the code for analysing the possible moves. 
I decided from the beginning to parametrize against the direction of the reversal starting from a given square,
so I encoded it in dr, dc variables and wrote it initially just for dr = 0, dc = -1 (test reversing from to the left).

After it worked, it turned out that to effectuate the move can be done by almost the same code, but we must
check for all the directions because one move can reverse opponents' discs in more than one direction.

As a byproduct of highlighting the possible moves, I get the coordinates of possible moves and their number. 
It allows to test easily whether "p" or any given move is a valid move.

Two successful passes's are fixed and lead to the game termination and the final stats screen.
