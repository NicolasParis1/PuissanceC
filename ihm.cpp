#include <SDL.h>
#include "ihm.h"
#undef main
#include <iostream>
//#include <conio.h>


//don't do this, this is just an example
SDL_Renderer* renderer;
SDL_Window* window;
bool isRunning;
bool fullscreen;
bool p4_unseted = true;



//please don't put all your code in main like I did.
int main_sdl() {
	init_window();
	int n_collum = 0;

	while (isRunning) {
		handleEvents(n_collum);
		render();
		update();
	}
	return 0;
}

//handles any events that SDL noticed.
void handleEvents(int& n_collum) {
	//the only event we'll check is the  SDL_QUIT event.
	SDL_Event event;
	SDL_PollEvent(&event);
	const char* state;
	int cu;
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYUP:
		state = SDL_GetKeyName(event.key.keysym.sym);
		//printf(state); 
		if (*state == 'A') {
			printf("A");
			n_collum = 1;
		}
		else if (*state == 'Z') {
			printf("Z");
			n_collum = 2;
		}
		else if (*state == 'E') {
			printf("E");
			n_collum = 3;
		}
		else if (*state == 'R') {
			printf("R");
			n_collum = 4;
		}
		else if (*state == 'T') {
			printf("T");
			n_collum = 5;
		}
		else if (*state == 'Y') {
			printf("Y");
			n_collum = 6;
		}
		else if (*state == 'U') {
			printf("U");
			n_collum = 7;
		}
		std::cout << n_collum;
	case SDL_KEYDOWN:

	default:
		break;
	}
}

//simple render function
void render() {
	//SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
	
	if (p4_unseted) {
		set_p4();
		//set_token(2, 3, 1);
		p4_unseted = false;
	}
	

	//your stuff to render would typically go here.
	SDL_RenderPresent(renderer);
}

void set_p4() {
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
	SDL_RenderPresent(renderer);
}

void set_token(int np, int i, int j) {
	/*	i between 1 and 7
		j between 1 and 6 
		np 1 or 2*/
	SDL_Rect rect;
	rect.x = 50 + 10 + (i-1) * 100;
	rect.y = 50 + 10 + (j-1) * 100;
	rect.w = 80;
	rect.h = 80;
	if (np = 1) {	/*player 1 (yellow)*/
		SDL_RenderDrawRect(renderer, &rect); //dessine le rectangle
		SDL_SetRenderDrawColor(renderer, 230, 230, 30, 255); //couleur
		SDL_RenderFillRect(renderer, &rect);//rempli le rectangle
		SDL_RenderPresent(renderer);
	}
	else {			/*player 2 (red)*/
		SDL_RenderDrawRect(renderer, &rect); //dessine le rectangle
		SDL_SetRenderDrawColor(renderer, 230, 20, 20, 255); //couleur
		SDL_RenderFillRect(renderer, &rect);//rempli le rectangle
		SDL_RenderPresent(renderer);
	}
	
}

//simple update function
void update() {
	//if things could update the code would go in here.
}



void init_window() {

	int flags = 0;
	flags = SDL_WINDOW_RESIZABLE;
	window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 700, flags);
	if (window) {
		std::cout << "Window Created!\n";
		//SDL_SetWindowMinimumSize(window, 100, 100);
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer) {
		SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255);
		std::cout << "Renderer created!\n";
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		isRunning = true;
	}
}


