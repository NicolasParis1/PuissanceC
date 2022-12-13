//
// Created by nicolas on 10/12/22.
//

#include <SDL2/SDL.h>

SDL_Renderer* renderer;
SDL_Window* window;


void initWindow() {
    int flags = 0;
    flags = SDL_WINDOW_RESIZABLE;
    window = SDL_CreateWindow("PuissanceC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 700, flags);

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
        SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        //isRunning = true;
    }
}


void setP4() {
    /*premier rectangle bleu*/
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
    SDL_Delay(200);
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
    SDL_RenderDrawRect(renderer, &rect); //dessine le rectangle
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