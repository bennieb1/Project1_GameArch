#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Player.h"
#include "Enemy.h"
#include <list>


class Game
{
private: 

	SDL_Window* window;
	SDL_Renderer* render;

	bool isrunning = true;

	Player* player;
	std::list<Enemy*> enemies;


public:

	Game();
	~Game();
	void run();
	void Render();
	void handledEvents();
	void Update();

	void Destroy();
};

