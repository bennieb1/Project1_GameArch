#include "Game.h"

Game::Game() {

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1240, 720, SDL_WINDOW_SHOWN);
	render = SDL_CreateRenderer(window, -1, 0);


	isrunning = true;
  

  

}