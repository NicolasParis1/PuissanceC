#include <stdio.h>
#include <stdbool.h>
#include "Game.h"


int main(int argc, char *argv[]) {
    if(argc == 1) {
        printf("mode local\n");

        //create and initialize the board
        int board[6][7];
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                board[i][j] = 0;
            }
        }

        bool p1_turn = true;    //the game begins with player1
        int victoriousPlayer;
        int i, j;
        do {
            if(p1_turn) {   //Player 1 turn, waiting for his input
                setToken(&board, i, j, 1);
            }
            else {  //player 2 turn, waiting for his move
                setToken(&board, i, j, 5);
            }
            p1_turn = !p1_turn; //flip to alternate player
        } while (!(victoriousPlayer=victoryCheck(&board, i, j)));

        printf("Player %d won !", victoriousPlayer);
    }
    else
        return 0;
    return 0;
}

