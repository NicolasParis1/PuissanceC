#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Game.h"
#include "network.h"
#include "minmax.h"
#include "ihm.h"


int main(int argc, char *argv[]) {

    /* create and initialize the board */
    int board[WIDTH+6][HEIGHT+6];
    for (int x = 0; x < WIDTH+6; ++x) {
        for (int y = 0; y < HEIGHT+6; ++y) {
            board[x][y] = 0;
        }
    }

    int i;
    bool p1_turn = true;    /* The game begins with player1, the human player */
    int victoriousPlayer;
    int j;
    int Nturn = 0;

    /* Graphic inits */
    initWindow();
    setP4();

    if (argc == 1) {    /* Local mode, no option */
        printf("Mode local\n");

        do {
            if(p1_turn) {   /* Player 1 turn, waiting for his input */
                do {
                    i=handleEvents();   /* Wait for the input */
                }
                while(!canPlayAt(&board, i));
                /* Place the token */
                j = placeTokenTop(&board, i, 1);
                setTokenVisual(1, i,j);
            }
            else {  /* player 2 turn, computing his move */
                j = computerMove(&board, 3, -1, &i);
                setTokenVisual(2, i,j);
            }
            Nturn ++;
            p1_turn = !p1_turn; /* flip to alternate player */
            print_array(&board);
        } while (!(victoriousPlayer=victoryCheck(&board, i, j)) && Nturn != 42);    /* play as long as no one won or if
                                                                                there are still valid move to make */
        if(Nturn == 42)
            printf("Draw !");
        else
            printf("Player %d won !", victoriousPlayer);

    } else if(argc==3) {    /* Multiplayer over network */
        int option = argv[1][1];
        int sock;
        int csock;
        if (option == 115) {    /* Server mode */
            printf("Mode serveur\n");
            int port = atoi(argv[2]);
            create_connection(port, &sock, &csock);

            /* Game */
            do {
                if(p1_turn) {   /* Player 1 turn, compute his move */
                    /* Place the token */
                    if(Nturn==0) {  /* First move */
                        i = 3;
                        j = placeTokenTop(&board, i, 1);
                    }
                    else {  /* Compute the move for real if it is not the first one */
                        j = computerMove(&board, 10, 1, &i);
                    }
                    setTokenVisual(1, i,j);
                    send_int(i, &csock);    /* Send horizontal position to client */
                }
                else {  /* player 2 turn, waiting for his input */
                    i = wait_for_int(&csock);
                    j = placeTokenTop(&board, i, -1);
                    setTokenVisual(2, i,j);
                }
                Nturn ++;
                p1_turn = !p1_turn; /* flip to alternate player */
                print_array(&board);
            } while (!(victoriousPlayer=victoryCheck(&board, i, j)) && Nturn != 42);    /* play as long as no one won or if
                                                                                there are still valid move to make */

            if(victoriousPlayer==-1) {
                victoriousPlayer = 2;
            }
            if(Nturn == 42)
                printf("Draw !");
            else
                printf("Player %d won !", victoriousPlayer);

            close_socket(&sock);
            close_socket(&csock);
        } else if (option == 99) {  /* client mode */
            printf("Mode client\n");
            char *token = strtok(argv[2], ":");
            char ip[16];
            strcpy(ip, token);
            token = strtok(NULL, ":");
            int port = atoi(token);
            connect_to(ip, port, &csock);

            /* Game */
            do {
                if(p1_turn) {   /* Player 1 turn, wait for his input */
                    /* Place the token */
                    i = wait_for_int(&csock);
                    j = placeTokenTop(&board, i, 1);
                    setTokenVisual(1, i,j);
                }
                else {  /* player 2 turn, compute his move */
                    j = computerMove(&board, 10, -1, &i);
                    send_int(i, &csock);
                    setTokenVisual(2, i,j);
                }
                Nturn ++;
                p1_turn = !p1_turn; /* flip to alternate player */
                print_array(&board);
            } while (!(victoriousPlayer=victoryCheck(&board, i, j)) && Nturn != 42);    /* play as long as no one won or if
                                                                                there are still valid move to make */

            if(victoriousPlayer==-1) {
                victoriousPlayer = 2;
            }
            if(Nturn == 42)
                printf("Draw !");
            else
                printf("Player %d won !", victoriousPlayer);

            close_socket(&csock);
        }
    }

    printf("\nSend any key to close the program...");
    scanf("%d", NULL);

    closeWindow();
    return 0;
}