//
// Created by nicolas on 013/09/22.
//

#ifndef PUISSANCEC_GAME_H
#define PUISSANCEC_GAME_H

#include <stdbool.h>

#define WIDTH 7
#define HEIGHT 6

void setToken(int (*board)[13][12], int i, int j, int v);
bool canPlayAtXY(int (*board)[13][12], int, int);
bool canPlayAt(int (*board)[13][12], int);
bool canPlay(int (*board)[13][12]);
int placeTokenTop(int (*board)[13][12], int x, int v);
void print_array(int (*)[13][12]);
int victoryCheck(int (*)[13][12], int, int);
int threeAligned(int (*)[13][12], int, int);
int twoAligned(int (*)[13][12], int, int);

#endif //PUISSANCEC_GAME_H
