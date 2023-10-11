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

	bool isrunning = false;

	Player* player;
	std::list<Enemy*> enemies;

	void handledEvents();
	void Update();
	void Render();
	void Destroy();


public:

	Game();
	~Game();
	void run();


};

