#include "minmax.h"
#include "Game.h"
#include <stdio.h>

/* https://en.wikipedia.org/wiki/Algorithme_minimax */
int minmax(int (*board)[13][12], int depth, bool maximizingPlayer, int x_played, int y_played) {
    print_array(board);
    /* If player has won */
    if(victoryCheck(board, x_played, y_played) != 0) {
        if (maximizingPlayer)
            return -100;
        else
            return 100;
    }

    /* If max depth reached or terminal node */
    if (depth == 0) // && !canPlay(&board)
        return 0;

    int best_score;
    if (maximizingPlayer) {
        best_score = -100;
        int score = best_score;
        for (int i = 0; i < WIDTH; ++i) {
            /* copy board */
            int board_cp[WIDTH + 6][HEIGHT + 6];
            for (int x = 0; x < WIDTH + 6; ++x) {
                for (int y = 0; y < HEIGHT + 6; ++y) {
                    board_cp[x][y] = (*board)[x][y];
                }
            }
            /* Play the move */
            int y = placeTokenTop(&board_cp, i, 1);
            /* Recursive call, keep the best score */
            score = minmax(&board_cp, depth - 1, false, i, y);
            if (score > best_score)
                best_score = score;
        }
    } else { /* Minimizing player */
        best_score = 100;
        int score = best_score;
        for (int i = 0; i < WIDTH; ++i) {
            /* copy board */
            int board_cp[WIDTH + 6][HEIGHT + 6];
            for (int x = 0; x < WIDTH + 6; ++x) {
                for (int y = 0; y < HEIGHT + 6; ++y) {
                    board_cp[x][y] = (*board)[x][y];
                }
            }
            /* Play the move */
            int y = placeTokenTop(&board_cp, i, -1);
            /* Recursive call, keep the best score */
            score = minmax(&board_cp, depth - 1, true, i, y);
            if (score < best_score)
                best_score = score;
        }
    }
    return best_score;
}
//TODO: tester minmax, elle a été testé que pour un cas très simple

//TODO: negamax ? pour éclaircir le code (ça évitera les erreurs aussi)

//TODO: faire un tableau des scores renvoyé par minmax dans la boucle de x pour déterminer quel pion jouer.
// L'idée étant de jouer le pion avec le score max et de recalculer tout après le tour de l'adversaire, c'est pas opti mais ça marchera

//TODO: Faire une fonction heuristique qui determine si un placement de pion est bon ou pas, pour le moment gagner=100, perdre=-100.
// Il faut les naunces entre. En se servant par exemple du nombre de 3 pions alignés (fonction à faire)
// En cas d'égalité entre plusieurs positions de pions, jouer la position la plus au centre ou aléatoire (à voir)
// Sans l'heuristique, ça risque d'être compliqué de trouver un bon coup sans dérouler l'arbre entier parce que la fonction
// suppose que l'adversaire joue son meilleur coup

//TODO: alpha beta pour pouvoir avoir une profondeur de recherche suffisante


