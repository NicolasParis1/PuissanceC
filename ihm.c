//
// Created by nicolas on 10/12/22.
//

#include <SDL2/SDL.h>
#include "Game.h"

SDL_Renderer* renderer;
SDL_Window* window;


void initWindow() {
    window = SDL_CreateWindow("PuissanceC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 700, 0);

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
        SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        //isRunning = true;
    }
}


void setP4() {
    /*premier rectangle bleu*/
    SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect;
    rect.x = 50;
    rect.y = 50;
    rect.w = 700;
    rect.h = 600;

    SDL_RenderDrawRect(renderer, &rect);//dessine le rectangle
    SDL_SetRenderDrawColor(renderer, 10, 10, 200, 205);//couleur
    SDL_RenderFillRect(renderer, &rect);//rempli le rectangle


    /*les 6*7 trous*/

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 6; j++) {
            rect.x = 50+10+i*100;
            rect.y = 50+10+j*100;
            rect.w = 80;
            rect.h = 80;

            SDL_RenderDrawRect(renderer, &rect); //dessine le rectangle
            SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255); //couleur
            SDL_RenderFillRect(renderer, &rect);//rempli le rectangle
        }
    }
    SDL_Delay(10);
    SDL_RenderPresent(renderer);
}


void setTokenVisual(int np, int i, int j) {
    /*	i between 1 and 7
        j between 1 and 6
        np 1 or 2*/

    SDL_Rect rect;
    rect.x = 50 + 10 + i * 100;
    rect.y = 50 + 10 + (5-j) * 100;
    rect.w = 80;
    rect.h = 80;
    //SDL_RenderDrawRect(renderer, &rect); //dessine le rectangle
    if (np == 1) {	/*player 1 (yellow)*/
        SDL_SetRenderDrawColor(renderer, 230, 230, 30, 255); //couleur
    }
    else {			/*player 2 (red)*/
        SDL_SetRenderDrawColor(renderer, 230, 20, 20, 255); //couleur
    }
    SDL_RenderFillRect(renderer, &rect);//rempli le rectangle
    SDL_Delay(200);
    SDL_RenderPresent(renderer);
}

void resetVisual(int (*board)[13][12]) {
    setP4();
    for (int x = 3; x < WIDTH + 3; ++x) {
        for (int y = 3; y < HEIGHT + 3; ++y) {
            if((*board)[x][y] != 0) {
                setTokenVisual((*board)[x][y], x-3, y-3);
            }
        }
    }
}

void drawWinner(int (*board)[13][12], int i, int j) {
    /* Essentially the winnerCheck function. Breaking instead of returning to extract dy and dx to use them to draw the
     * line over the winning tokens */

    i=i+3;
    j=j+3;
    int player = (*board)[i][j];

    bool isVertical = false;

    //Vertical check
    if (j >= 3)
        if ((*board)[i][j - 1] == player && (*board)[i][j - 2] == player && (*board)[i][j - 3] == player) {
            /* If the winning tokens are vertically aligned, the i,j token is on top and the bottom one is at i,j-3 */
            SDL_Rect rect;
            rect.x = 50 + 30 + i * 100;
            rect.y = 50 + 30 + (5-j) * 100;
            rect.w = 80;
            rect.h = 80*4;
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            SDL_RenderFillRect(renderer, &rect);//rempli le rectangle
            SDL_Delay(200);
            SDL_RenderPresent(renderer);
            return;
        }
/*
    if(!isVertical)
    //Both diagonals and horizontal
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = 0; dx <= 3; ++dx) {
            if ((*board)[x + dx - 3][y+dy*3-dx*dy] == player && (*board)[x + dx - 2][y + dy*2-dx*dy] == player &&
                (*board)[x + dx - 1][y + dy-dx*dy] == player && (*board)[x + dx][y-dx*dy] == player)
                return player;
        }
    }
*/
}

void closeWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


//handles any events that SDL noticed.
int handleEvents() {
    //the only event we'll check is the  SDL_QUIT event.
    SDL_Event event;
    //SDL_PollEvent(&event);
    while(1) {
        SDL_WaitEvent(&event);
        const char *state;
        switch (event.type) {
            //case SDL_QUIT:
            //return -2;
            //break;
            case SDL_KEYUP:
                state = SDL_GetKeyName(event.key.keysym.sym);
                switch (*state) {
                    case 'A':
                        return 0;
                        break;
                    case 'Z':
                        return 1;
                        break;
                    case 'E':
                        return 2;
                        break;
                    case 'R':
                        return 3;
                        break;
                    case 'T':
                        return 4;
                        break;
                    case 'Y':
                        return 5;
                        break;
                    case 'U':
                        return 6;
                        break;
                    default:
                        break;
                }
                //case SDL_KEYDOWN:
            default:
                break;
        }
    }
}