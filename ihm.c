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
    }
}

void drawCircle(int xc, int yc, int r) {
    for (int w = 0; w < r * 2; w++) {
        for (int h = 0; h < r * 2; h++) {
            int dx = r - w;
            int dy = r - h;
            if ((dx*dx + dy*dy) < (r * r)) {
                SDL_RenderDrawPoint(renderer, xc + dx, yc + dy);
            }
        }
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
    int x;
    int y;
    int r = 40;

    SDL_RenderDrawRect(renderer, &rect);//dessine le rectangle
    SDL_SetRenderDrawColor(renderer, 20, 30, 200, 255);//couleur
    SDL_RenderFillRect(renderer, &rect);//rempli le rectangle


    /*les 6*7 trous*/
    SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255);
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 6; j++) {
            x = 50 + 30 + (i * 100 + 20);
            y = 50 + 30 + (j * 100 + 20);

            drawCircle(x, y, r);
        }
    }

    SDL_Delay(10);
    SDL_RenderPresent(renderer);
}


void setTokenVisual(int np, int x, int y) {
    /*	i between 1 and 7
        j between 1 and 6
        np 1 or 2*/
    int speed = 15;
    for (int j = 6; j >= y  ; j--) {
        /* erase */
        int xc = 50 + 30 + x * 100 + 20;
        int yc = 50 + 30 + (4-j) * 100 + 20;
        int r = 40;
        SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255); //couleur
        drawCircle(xc, yc, r);
        SDL_Delay(speed);

        yc = 50 + 30 + (5-j) * 100 + 20;

        //SDL_RenderDrawRect(renderer, &rect); //dessine le rectangle
        if (np == 1) {	/*player 1 (yellow)*/
            SDL_SetRenderDrawColor(renderer, 230, 230, 30, 255); //couleur
        }
        else {			/*player 2 (red)*/
            SDL_SetRenderDrawColor(renderer, 230, 20, 20, 255); //couleur
        }
        drawCircle(xc, yc, r);
        SDL_Delay(speed);
        SDL_RenderPresent(renderer);
    }
    SDL_Delay(200);
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

void drawWinner(int (*board)[13][12]) {
    /* Essentially the winnerCheck function */

    for (int y = 3; y < HEIGHT + 3; ++y) {
        for (int x = 3; x < WIDTH + 3; ++x) {
            int player = (*board)[x][y];
            if(player != 0) {
                int xc, yc;
                int r = 40;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); /* set color */

                /* Vertical check */
                if (y >= 3)
                    if ((*board)[x][y - 1] == player && (*board)[x][y - 2] == player && (*board)[x][y - 3] == player) {
                        int x1 = 50 + 30 + (x-3) * 100 + 20;
                        int y1 = 50 + 30 + (y - 1 - 3) * 100 + 20;
                        int y2 = 50 + 30 + (y + 2 - 3) * 100 + 20;
                        SDL_RenderDrawLine(renderer, x1-2, y1, x1-1, y2);
                        SDL_RenderDrawLine(renderer, x1-1, y1, x1-2, y2);
                        SDL_RenderDrawLine(renderer, x1, y1, x1, y2);
                        SDL_RenderDrawLine(renderer, x1+1, y1, x1+1, y2);
                        SDL_RenderDrawLine(renderer, x1+2, y1, x1+2, y2);
                        SDL_RenderPresent(renderer);
                        return;
                    }

                /* Both diagonals and horizontal */
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dx = 0; dx <= 3; ++dx) {
                        if ((*board)[x + dx - 3][y + dy * 3 - dx * dy] == player &&
                            (*board)[x + dx - 2][y + dy * 2 - dx * dy] == player &&
                            (*board)[x + dx - 1][y + dy - dx * dy] == player &&
                            (*board)[x + dx][y - dx * dy] == player) {

                            int x1 = 50 + 30 + (x + dx - 3 - 3) * 100 + 20;
                            int y1 = 50 + 30 + (y - dy * 3 + dx * dy + 2) * 100 + 20;
                            int x2 = 50 + 30 + (x + dx - 3) * 100 + 20;
                            int y2 = 50 + 30 + (y + dx * dy + 2) * 100 + 20;
                            SDL_RenderDrawLine(renderer, x1, y1-2, x2, y2-2);
                            SDL_RenderDrawLine(renderer, x1, y1-1, x2, y2-1);
                            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
                            SDL_RenderDrawLine(renderer, x1, y1+1, x2, y2+1);
                            SDL_RenderDrawLine(renderer, x1, y1+2, x2, y2+2);
                            SDL_RenderPresent(renderer);
                            return;
                        }
                    }
                }
            }
        }
    }
}

void closeWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


//handles any events that SDL noticed.
int handleEvents() {
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
                    case 'Z':
                        return 1;
                    case 'E':
                        return 2;
                    case 'R':
                        return 3;
                    case 'T':
                        return 4;
                    case 'Y':
                        return 5;
                    case 'U':
                        return 6;
                    default:
                        break;
                }
                //case SDL_KEYDOWN:
            default:
                break;
        }
    }
}