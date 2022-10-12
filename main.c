#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Game.h"
#include "solver.h"
#include "network.h"


int main(int argc, char *argv[]) {
    if(argc == 1) {
        printf("mode local\n");
        srand(time(NULL));
        //printf("%i", time(NULL));
        //create and initialize the board
        int board[7][6];
        for (int x = 0; x < 7; ++x) {
            for (int y = 0; y < 6; ++y) {
                board[x][y] = 0;
            }
        }

        //Solver
        int position[43];
        for (int i = 0; i < 43; ++i) {
            position[i] = -1;
        }

        char str[42] = "2252576253462244111563365343671351441";
        int i =0;
        while(str[i]!='\0') {
            position[i] = str[i]-49;
            i++;
        }

        for (int j = 0; j < 42; ++j) {
            printf("%d",position[j]);
        }

        int score = negamax_start(position);
        printf("%d", score);

        /*

        bool p1_turn = true;    //the game begins with player1
        int victoriousPlayer;
        int i, j;
        int Nturn = 0;
        do {
            if(p1_turn) {   //Player 1 turn, waiting for his input
                do {
                    i = rand() % 7;
                }
                while(board[i][5] != 0);
                j = placeTokenTop(&board, i, 1);
            }
            else {  //player 2 turn, waiting for his move
                do {
                    i = rand() % 7;
                }
                while(board[i][5] != 0);
                j = placeTokenTop(&board, i, 5);
            }
            Nturn ++;
            p1_turn = !p1_turn; //flip to alternate player
            print_array(&board);
        } while (!(victoriousPlayer=victoryCheck(&board, i, j)) && Nturn != 42);    // play as long as no one won or if
        // there are still valid move to make
        if(Nturn == 42)
            printf("Draw !");
        else
            printf("Player %d won !", victoriousPlayer);

    }
    else if(argc==3) {
        int option = argv[1][1];
        if(option==115) {    //server
            int port = atoi(argv[2]);
            SOCKET sock;
            SOCKET csock;
            createSocket(port, sock, csock);
            closeSocket(sock, csock);

        }
        else if(option==99) {  //client
            char* token = strtok(argv[2], ":");
            char ip[16];
            strcpy(ip, token);
            token = strtok(NULL, ":");
            int port = atoi(token);

            int csock = connectSocket(ip, port);
            closeClient(csock);
        }
        return 0;
        */
    }
    return 0;
}

