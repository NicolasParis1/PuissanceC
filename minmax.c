#include "minmax.h"
#include "Game.h"
#include <stdio.h>
#include <malloc.h>

/* https://en.wikipedia.org/wiki/Negamax */

/* Implementation of a minmax algorithm to allow the computer to play. Uses the negamax and alpha beta optimizations. */
int minmax(int (*board)[13][12], int depth, int alpha, int beta, int player, int x_played, int y_played) {

    //print_array(board);
    /* If player has won, we can return early */
    if(victoryCheck(board, x_played, y_played) != 0) {
        return 999999999*player;
    }

    /* If max depth reached or terminal node */
    if (depth == 0 || !canPlay(board)) {    /* Heuristic */
        return heuristic(board) * player;
        //return -threeAligned(board, x_played, y_played) * 50 - twoAligned(board, x_played, y_played) * 20;
    }

    int best_score = -999999999;
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
            score = -minmax(&board_cp, depth - 1, -beta, -alpha, -player, i, y);
            //printf("\n\n%d", score);
            if (score >= beta)
                return score;
            if (score > alpha)
                alpha = score;
        }
    }
    //printf("\n\nMeilleur score : %d\n", best_score);
    return alpha;
}

int minmax_no_heuristic(int (*board)[13][12], int depth, int alpha, int beta, int player, int x_played, int y_played) {

    //print_array(board);
    /* If player has won, we can return early */
    if(victoryCheck(board, x_played, y_played) != 0) {
        return 999999999*player;
    }

    /* If max depth reached or terminal node */
    if (depth == 0 || !canPlay(board)) {    /* Heuristic */
        return 0;
        //return -threeAligned(board, x_played, y_played) * 50 - twoAligned(board, x_played, y_played) * 20;
    }

    int best_score = -1999999999;
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
            score = -minmax_no_heuristic(&board_cp, depth - 1, -beta, -alpha, -player, i, y);
            //printf("\n\n%d", score);
            if (score >= beta)
                return score;
            if (score > alpha)
                alpha = score;
        }
    }
    //printf("\n\nMeilleur score : %d\n", best_score);
    return alpha;
}

void freeCountingBoard(int **board) {
    for (int i = 0; i < WIDTH; ++i) {
        free(board[i]);
    }
    free(board);
}

int heuristic(int (*board)[13][12]) {
    /* Init a space the same size as the board to know if a token as already been counted in a alignment. */
    int **countingBoard = malloc(WIDTH*sizeof(int*));
    for (int x = 0; x < WIDTH; ++x) {
        countingBoard[x] = malloc(HEIGHT*sizeof(int*));
        for (int y = 0; y < HEIGHT; ++y) {
            countingBoard[x][y] = 0;
        }
    }

    int value = 0; /* Heuristic value */
    for (int x = 3; x < WIDTH + 3; ++x) {
        for (int y = HEIGHT + 3; y > 2; --y) {
            int i = 1; /* Vertical alignment counter */
            //int j_left = 0; /* Horizontal alignment counter */
            //int j_right = 0; /* Horizontal alignment counter */
            int TokenV = (*board)[x][y];
            /* Count the number of vertically aligned tokens */
            if(TokenV!=0) {
                while ((*board)[x][y - i] == TokenV) {
                    i++;
                }

                switch (i) {
                    case 1 : /* No vertical alignment */
                        break;

                    case 2 : {/* Vertical alignment of 2 */
                        /* Count the number of available square above it */
                        int j=1;
                        while (((*board)[x][y + j] == 0) && ((y + j) < (HEIGHT + 2))) {
                            j++;
                        }
                        switch (j) {
                            case 2 :
                                value += 10000 * TokenV;
                                break;
                            case 3 :
                                value += 20000 * TokenV;
                                break;
                            case 4 :
                                value += 30000 * TokenV;
                                break;
                            case 5 :
                                value += 40000 * TokenV;
                                break;
                            default :
                                break;  /* The alignment won't lead anywhere because there is no free space to do a 4 alignment */
                        }
                        break;}

                    case 3 :    /* Vertical alignment of 3 */
                        if ((*board)[x][y + 1] == 0) { /* If the space above it is free */
                            value += 900000 * TokenV;
                        }
                        break;

                    case 4 :    /* Vertical alignment of 4 */
                        freeCountingBoard(countingBoard);
                        return 999999999 * TokenV; /* We can stop here, the game has been won */

                    default :
                        break; //TODO: Check it doesn't happen
                }
                if(i!=1) {
                    for (int k = 0; k < i; ++k) {
                        countingBoard[x-3][y - k-3] = 1;
                    }
                }

                /* Count the number of horizontally and diagonally aligned tokens */
                int maxI = 1;
                int maxDx = -0;
                int maxDy = -1;

                /* Find an alignment */
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dx = 0; dx <= 3; ++dx) {
                        i = 1; /* Reset the counter */
                        while ((*board)[x + dx - i][y + dy * i - dx * dy] == TokenV) {
                            i++;
                        }
                        if (i > maxI) {
                            maxI = i-1; //TODO: -1 ou pas ?
                            maxDx = dx;
                            maxDy = dy;
                        }
                    }
                }
                bool newAlignment = false;

                for (int k = 1; k < maxI; ++k) {
                    if(countingBoard[(x + maxDx - k)-3][(y + maxDy * k - maxDx * maxDy)-3]==0) {
                        newAlignment = true;
                    }
                }
                if(newAlignment) {
                    /* Count the alignment */
                    for (int k = 1; k <= maxI; ++k) {
                        countingBoard[(x + maxDx - k)-3][(y + maxDy * k - maxDx * maxDy)-3] = 1;
                    }

                    /* Attribute a value to the alignment */
                    switch (maxI) {
                        case 1 : /* No alignment, already counted before */
                            break;

                        case 2 : {    /* Alignment of 2 */
                            //TODO: add the case where there is a token separated by an empty square, count as an alignment of 3
                            int j_left = 0; /* Reset the counters */
                            int j_right = 0;
                            /* Count the number of adjacent playable square */
                            while(canPlayAtXY(board, x + maxDx - (maxI + j_left + 1), y + maxDy * (maxI + j_left + 1) - maxDx * maxDy)) {
                                j_left++;
                            }
                            while (canPlayAtXY(board, x + maxDx + (j_right), y - maxDy * (j_right) - maxDx * maxDy)) {
                                j_right++;
                            }
                            switch (j_left + j_right) {
                                case 2 :
                                    value += 10000 * TokenV;
                                    break;
                                case 3 :
                                    value += 20000 * TokenV;
                                    break;
                                case 4 :
                                    value += 30000 * TokenV;
                                    break;
                                case 5 :
                                    value += 40000 * TokenV;
                                    break;
                                default :
                                    break;  /* The alignment won't lead anywhere because there is no free space to do a 4 alignment */
                            }
                            break;}

                        case 3 :    /* Alignment of 3 */
                            if (canPlayAtXY(board, x + maxDx - (maxI + 1), y + maxDy * (maxI + 1) - maxDx * maxDy) &&
                                canPlayAtXY(board, x + maxDx, y - maxDx * maxDy)) {  /* If a move can be made on either direction, the game will be won */
                                freeCountingBoard(countingBoard);
                                return 999999999 * TokenV;
                            } else if (canPlayAtXY(board, x + maxDx - (maxI + 1), y + maxDy * (maxI + 1) - maxDx * maxDy) ||
                                       canPlayAtXY(board, x + maxDx, y - maxDx * maxDy)) { /* If a move can be made on only of the adjacent square */
                                value += 900000 * TokenV;
                            }
                            break;

                        case 4 :    /* Alignment of 4 */
                            freeCountingBoard(countingBoard);
                            return 999999999 * TokenV; /* We can stop here, the game has been won */

                        default :
                            break;  //TODO: Check it doesn't happen

                    }
                }
                /* No alignment */
                if(countingBoard[x-3][y-3] == 0) {
                    switch (x-3) {
                        case 3 :
                            value += 200 * TokenV;
                            break;
                        case 2 :
                        case 4 :
                            value += 120 * TokenV;
                            break;
                        case 1 :
                        case 5 :
                            value += 70 * TokenV;
                            break;
                        case 0 :
                        case 6 :
                            value += 40 * TokenV;
                            break;
                        default :
                            break;    //TODO: check it doesn't happen
                    }
                }
            }
        }
    }
    //printf("\n%d\n", value);
    freeCountingBoard(countingBoard);
    return value;
}

int computerMove(int (*board)[13][12], int depth, int player, int* i) {
    int column;
    int best_score= -1999999999;
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
                score = -minmax(&board_cp, depth - 1, -1999999999, 1999999999, -player, *i, y);
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
