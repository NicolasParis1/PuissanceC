//
// Created by nicolas on 07/09/22.
//

#ifndef PUISSANCEC_GAME_H
#define PUISSANCEC_GAME_H

#include <stdbool.h>

void setToken(int (*board)[6][7], int i, int j, int v);
void print_array2(const int (*)[6][7]);
int victoryCheck(int (*)[6][7], int, int);

#endif //PUISSANCEC_GAME_H
