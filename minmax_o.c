#include "minmax.h"
#include "Game.h"
#include <stdio.h>
#include "ihm.h"

/* https://en.wikipedia.org/wiki/Minimax */
int minmax(int (*board)[13][12], int depth, int player, int x_played, int y_played) {

    //print_array(board);
    /* If player has won */
    if(victoryCheck(board, x_played, y_played) != 0) {
        return 100*player;
    }

    /* If max depth reached or terminal node */
    if (depth == 0 || !canPlay(board)) {    /* Heuristic */
        return -threeAligned(board, x_played, y_played) * 50 - twoAligned(board, x_played, y_played) * 20;
    }

    int best_score = -1000;
    int score = best_score;
    //for (int i = 0; i < WIDTH; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
        int i;
        switch (j) {    // Modified sequence, favors center columns
            case 0:
                i=3; break;
            case 1:
                i=2; break;
            case 2:
                i=4; break;
            case 3:
                i=1; break;
            case 4:
                i=5; break;
            case 5:
                i=0; break;
            case 6:
                i=6; break;
            default :
                i=j; break;
        }
        if (canPlayAt(board, i)) {
            /* copy board */
            int board_cp[WIDTH + 6][HEIGHT + 6];
            for (int x = 0; x < WIDTH + 6; ++x) {
                for (int y = 0; y < HEIGHT + 6; ++y) {
                    board_cp[x][y] = (*board)[x][y];
                }
            }
            /* Play the move */
            int y = placeTokenTop(&board_cp, i, player);
            /* Recursive call, keep the best score */
            score = -minmax(&board_cp, depth - 1, -player, i, y);
            //printf("\n\n%d", score);
            if (score > best_score)
                best_score = score;
        }
    }
    //printf("\n\nMeilleur score : %d\n", best_score);
    return best_score;
}

int computerMove(int (*board)[13][12], int depth, int player, int* i) {
    int column;
    int best_score= -1000;
    int score = best_score;
    //for (*i = 0; *i < WIDTH; ++*i) {
    for (int j = 0; j < WIDTH; ++j) {
        switch (j) {    // Modified sequence, gives better results
            case 0:
                *i=3; break;
            case 1:
                *i=2; break;
            case 2:
                *i=4; break;
            case 3:
                *i=1; break;
            case 4:
                *i=5; break;
            case 5:
                *i=0; break;
            case 6:
                *i=6; break;
            default :
                *i=j; break;
        }
        if(canPlayAt(board, *i)) {
            /* copy board */
            int board_cp[WIDTH + 6][HEIGHT + 6];
            for (int x = 0; x < WIDTH + 6; ++x) {
                for (int y = 0; y < HEIGHT + 6; ++y) {
                    board_cp[x][y] = (*board)[x][y];
                }
            }
            /* Play the move on the fake board */
            int y = placeTokenTop(&board_cp, *i, player);

            if(victoryCheck(&board_cp, *i, y) != 0) {   /* If we can win, play the move for real */
                column = *i;
                break;
            }
            else { /* else, recursive call the minimax algorithm, keep the best score */
                score = -minmax(&board_cp, depth - 1, -player, *i, y);
                //printf("score de cette branche %d\n", score);
                if (score > best_score) {
                    best_score = score;
                    column = *i;
                }
            }
        }
    }
    //printf("\n\nMeilleur score total : %d\n", best_score);
    /* Play the best move */
    int y = placeTokenTop(board, column, player);
    *i=column;
    return y;
}