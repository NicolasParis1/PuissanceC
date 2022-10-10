//
// Created by nicolas on 07/09/22.
//

#ifndef PUISSANCEC_GAME_H
#define PUISSANCEC_GAME_H

#include <stdbool.h>

void setToken(int (*board)[7][6], int i, int j, int v);
int placeTokenTop(int (*board)[7][6], int x, int v);
void print_array(int (*)[7][6]);
int victoryCheck(int (*)[7][6], int, int);

#endif //PUISSANCEC_GAME_H
