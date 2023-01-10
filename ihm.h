#pragma once

#ifndef IHM_H
#define IHM_H

//void handleEvents(int& n_collum); /*n_collum : colonne choisi avec le clavier*/
//void update();
//void render();
//void init_window();
//void set_p4();
//void set_token(int np, int i, int j); /*np: num player, i: collum, j: line
//									  affiche le jeton de couleur (np) à
//									  l'emplacement i et j*/


void initWindow();
void setP4();
void resetVisual(int (*board)[13][12]);
void drawWinner(int (*board)[13][12], int, int);
void setTokenVisual(int, int, int);
void closeWindow();
int handleEvents();
void drawCircle(int xc, int yc, int r);

#endif
