//
// Created by nicolas on 07/09/22.
//

#include "Game.h"
#include <stdio.h>

void setToken(int (*board)[6][7], int i, int j, int v) {
    (*board)[i][j] = v;
}

void print_array2(const int (*board)[6][7])
{
    printf("board:\n");
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            printf("%i ", (*board)[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int victoryCheck(int (*board)[6][7], int x, int y) {
    // (There is only a handful of positions to check to know if the game ended or not. Knowing the position of the
    // last token played, we can check only the sets of 4 tokens in which the last position is)
    // Player 1 is placing token as 1 in the board, player 2 is placing 5s. If the sum of the set is equal to 4, player1
    // wins, if it's equal to 20, player 2 wins
    
    //Horizontal check
    int sum = 0;
    for (int k = 0; k < 4; ++k) {
        sum += (*board)[k][y];
        if(sum == 4)
            return 1;
        else if(sum == 20)
            return 2;
        sum = 0;
    }

    //Vertical check
    for (int k = 0; k < 5; ++k) {
        sum += (*board)[x][k];
        if(sum == 4)
            return 1;
        else if(sum == 20)
            return 2;
        sum = 0;
    }

    // Ascending diagonal check
    //TODO: check out of bound errors
    for (int i = 0; i < 4; ++i) {
        sum=(*board)[x+i-3][y+i-3] + (*board)[x+i-2][y+i-2] + (*board)[x+i-1][y+i-1] + (*board)[x+i][y+i];
        if(sum == 4)
            return 1;
        else if(sum == 20)
            return 2;
        sum = 0;
    }

    // Descending diagonal check
    //TODO: check out of bound errors
    for (int i = 0; i < 4; ++i) {
        sum=(*board)[x-i-3][y-i+3] + (*board)[x-i+2][y-i+2] + (*board)[x-i+1][y-i+1] + (*board)[x-i][y-i];
        if(sum == 4)
            return 1;
        else if(sum == 20)
            return 2;
        sum = 0;
    }

    return 0;
}