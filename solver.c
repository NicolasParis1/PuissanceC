//
// Created by nicolas on 12/09/22.
//

#include "solver.h"
#include "Game.h"
#include <stdio.h>


/*
http://blog.gamesolver.org/solving-connect-four/01-introduction/
Implementation of the minimax algorithm. Recursively solve connect 4 using the negamax variant.
 */

int negamax_start(int *position) {
    int a, b;
    int position_cpy[42];
    b=-41;
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 42; ++j) {
            position_cpy[j] = position[j];
        }
        if(canPlay(position_cpy, i)) {
            a = negamax(position_cpy, i);
            if (a > b)
                b = a;
        }
    }
    return b;
}

int negamax(int *position, int col) {
    int n_moves = NMovesFromStart(position);
    //position[n_moves]=col;

    if(n_moves>=41)
        return 0;   //draw

    for (int x = 0; x < 7; ++x) //check if next move is winning
        if(canPlay(position, x))
            if(isWinningMove(position, x))
                return (42-n_moves)/2;

    int best_score = -41;

    for (int x = 0; x < 7; ++x) {
        if(canPlay(position, x)) {
            position[n_moves] = x;
            int score = -negamax(position, x);
            if(score > best_score)
                best_score=score;
        }
    }
    return best_score;
}

int NMovesFromStart(int *position) {
    int i = 0;
    while(position[i] != -1) {
        i++;
    }
    return i;
}

bool canPlay(int *position, int col) {
    int col_count = 0;
    for (int i = 0; i < 42; ++i) {
        if(position[i]==col) {
            col_count++;
        }
    }
    if (col_count==6) {
        return false;
    }
    return true;
}

bool isWinningMove(int *position, int col) {
    int n_moves = NMovesFromStart(position);
    int isWin = victoryCheckFromPosition(position, col);
    if(isWin==1)
        return true;
    else
        return false;
}