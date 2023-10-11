#include "Player.h"
#include <iostream>


Player::Player(SDL_Renderer* render) {

	SDL_Surface* player = IMG_Load("C:\\Users\\bennieb\\Documents\\GameArchitecture\\Project1\\Project1\\prog50049.project1.resources\\Mainplayer\\player.png");

	if (player == NULL) {
	
		std::cout << "Unable to load image!SDL_image Error " << IMG_GetError() << std::endl;

		text = nullptr;

	}
	else {
		text = SDL_CreateTextureFromSurface(render, player);
		SDL_FreeSurface(player);
	}
}
SDL_Texture* Player::getTexture() {
	return text;
}