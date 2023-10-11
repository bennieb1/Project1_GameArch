#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>

class Player
{
private:
	SDL_Texture* text;

public:
	Player(SDL_Renderer* render);
	~Player();

	SDL_Texture* getTexture();

	void Render(SDL_Renderer* renderer);



};

#endif