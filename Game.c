//
// Created by nicolas on 07/09/22.
//

#include "Game.h"
#include <stdio.h>

void setToken(int (*board)[7][6], int i, int j, int v) {
    (*board)[i][j] = v;
}

void print_array2(const int (*board)[7][6])
{
    printf("board:\n");
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            printf("%i ", (*board)[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int victoryCheck(int (*board)[7][6], int x, int y) {
    // (There is only a handful of positions to check to know if the game ended or not. Knowing the position of the
    // last token played, we can check only the sets of 4 tokens in which the last position is)
    // Player 1 is placing token as 1 in the board, player 2 is placing 5s. If the sum of the set is equal to 4, player1
    // wins, if it's equal to 20, player 2 wins

    //Horizontal check
    for (int i = 0; i < 4; ++i) {   //number of checks to do
        int sum = 0;
        for (int k = 0; k < 4; ++k) //summing the row
            sum += (*board)[i+k][y];
        if(sum == 4)
            return 1;
        else if(sum == 20)
            return 2;
    }

    //Vertical check
    for (int i = 0; i < 5; ++i) {
        int sum = 0;
        for (int k = 0; k < 4; ++k)
            sum += (*board)[x][i+k];
        if (sum == 4)
            return 1;
        else if (sum == 20)
            return 2;
    }

    // Ascending diagonal check
    if(x - y > - 2 && x - y < 3) {
        if (x - y > 0) { //below the center diagonal
            for (int i = 0; i < 7 - 4 - (x - y) + 1; ++i) {   // 7 is the max row, 4 account for the starting row
                int sum = 0;
                for (int k = 0; k < 4; ++k)
                    sum += (*board)[i + x - y][i];
                if (sum == 4)
                    return 1;
                else if (sum == 20)
                    return 2;
            }
        } else {  //above the center diagonal
            for (int i = 0; i < 6 - 4 - (y - x) + 1; ++i) {
                int sum = 0;
                for (int k = 0; k < 4; ++k)
                    sum += (*board)[i][i + x - y];
                if (sum == 4)
                    return 1;
                else if (sum == 20)
                    return 2;
            }
        }
    }

    return 0;
}