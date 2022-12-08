//
// Created by nicolas on 013/09/22.
//

#include "Game.h"
#include <stdio.h>

int placeTokenTop(int (*board)[13][12], int x, int v) {
    int i = 8;
    while((*board)[x+3][i]==0 && i>=3)
        i--;
    setToken(board, x+3, i+1, v);
    return i-2;
}

void setToken(int (*board)[13][12], int i, int j, int v) {
    (*board)[i][j] = v;
}

void print_array(int (*board)[13][12])
{
    printf("board:\n");
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            printf("%i ", (*board)[j][11-i]);  //flipped
        }
        printf("\n");
    }
    printf("\n");
}

int victoryCheck(int (*board)[13][12], int x, int y) {
    x+=3;
    y+=3;
    int player = (*board)[x][y];

    //Vertical check
    if (y >= 3)
        if ((*board)[x][y - 1] == player && (*board)[x][y - 2] == player && (*board)[x][y - 3] == player)
            return player;

    //Both diagonals and horizontal
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = 0; dx <= 3; ++dx) {
            if ((*board)[x + dx][y+dy*3] == player && (*board)[x + dx - 1][y + dy*2] == player &&
                (*board)[x + dx - 2][y + dy] == player && (*board)[x + dx - 3][y] == player)
                return player;
        }
    }

    return 0;
}