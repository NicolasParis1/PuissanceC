//
// Created by nicolas on 09/11/22.
//

#ifndef PUISSANCEC_MINMAX_H
#define PUISSANCEC_MINMAX_H

#include <stdbool.h>

int minmax(int (*board)[13][12], int, int, int, int);
int computerMove(int (*board)[13][12], int, int, int*);

#endif //PUISSANCEC_MINMAX_H
