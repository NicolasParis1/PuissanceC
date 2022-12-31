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

bool canPlay(int (*board)[13][12]) {
    for (int i = 0; i < WIDTH; ++i) {
        if(canPlayAt(board, i))
            return true;
    }
    return false;
}
bool canPlayAt(int (*board)[13][12], int x) {
    if((*board)[x+3][HEIGHT+2]==0)
        return true;
    else
        return false;
}
bool canPlayAtXY(int (*board)[13][12], int x, int y) {
    //if((*board)[x][y]==0 && ((*board)[x][y-1]!=0 || y==3) && y < HEIGHT + 2 && x > 2 && x < WIDTH + 3)    //TODO: mieux ?
    if((*board)[x][y]==0 && y > 2 && y < HEIGHT + 2 && x > 2 && x < WIDTH + 3)
        return true;
    else
        return false;
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
            if((*board)[j][11-i]==-1)
                printf("%i ", 2);
            else
                printf("%i ", (*board)[j][11-i]);  //flipped
        }
        printf("\n");
    }
    printf("\n");
}

int victoryCheck(int (*board)[13][12], int x, int y) {
    x=x+3;
    y=y+3;
    int player = (*board)[x][y];

    //Vertical check
    if (y >= 3)
        if ((*board)[x][y - 1] == player && (*board)[x][y - 2] == player && (*board)[x][y - 3] == player)
            return player;

    //Both diagonals and horizontal
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = 0; dx <= 3; ++dx) {
            if ((*board)[x + dx - 3][y+dy*3-dx*dy] == player && (*board)[x + dx - 2][y + dy*2-dx*dy] == player &&
                (*board)[x + dx - 1][y + dy-dx*dy] == player && (*board)[x + dx][y-dx*dy] == player)
                return player;
        }
    }

    return 0;
}


int threeAligned(int (*board)[13][12], int x, int y) {
    x=x+3;
    y=y+3;
    int player = (*board)[x][y];

    //Vertical check
    if (y >= 2)
        if ((*board)[x][y - 1] == player && (*board)[x][y - 2] == player)
            return player;

    //Both diagonals and horizontal
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = 0; dx <= 2; ++dx) {
            if ((*board)[x + dx - 2][y + dy*2-dx*dy] == player &&
                (*board)[x + dx - 1][y + dy-dx*dy] == player && (*board)[x + dx][y-dx*dy] == player)
                return player;
        }
    }

    return 0;
}

int twoAligned(int (*board)[13][12], int x, int y) {
    x=x+3;
    y=y+3;
    int player = (*board)[x][y];

    //Vertical check
    if (y >= 1)
        if ((*board)[x][y - 1] == player)
            return player;

    //Both diagonals and horizontal
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = 0; dx <= 1; ++dx) {
            if ((*board)[x + dx - 1][y + dy-dx*dy] == player && (*board)[x + dx][y-dx*dy] == player)
                return player;
        }
    }

    return 0;
}