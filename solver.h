//
// Created by nicolas on 12/09/22.
//

#ifndef PUISSANCEC_SOLVER_H
#define PUISSANCEC_SOLVER_H

#include <stdbool.h>

int negamax(int *position, int col);
int negamax_start(int *position);
int NMovesFromStart(int *);
bool canPlay(int *, int);
bool isWinningMove(int *, int);

#endif //PUISSANCEC_SOLVER_H
