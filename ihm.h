#pragma once

#ifndef IHM_H
#define IHM_H

void initWindow();
void setP4();
void resetVisual(int (*board)[13][12]);
void drawWinner(int (*board)[13][12]);
void setTokenVisual(int, int, int);
void closeWindow();
int handleEvents();
void drawCircle(int xc, int yc, int r);

#endif
