#pragma once

#ifndef IHM_H
#define IHM_H

void handleEvents(int& n_collum); /*n_collum : colonne choisi avec le clavier*/
void update();
void render();
void init_window();
void set_p4();
void set_token(int np, int i, int j); /*np: num player, i: collum, j: line
									  affiche le jeton de couleur (np) à 
									  l'emplacement i et j*/ 

#endif
