//
// Created by nicolas on 12/09/22.
//

#include "solver.h"
#include "Game.h"


/*
http://blog.gamesolver.org/solving-connect-four/01-introduction/
Implementation of the minimax algorithm. Recursively solve connect 4 using the negamax variant.
 */
int negamax(int x, int y) {

}

int NMovesFromStart(int *position) {
    int i = 0;
    while(position[i] != 0) {
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

}