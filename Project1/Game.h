#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Player.h"
#include "Enemy.h"
#include "Astroid.h"
#include <list>
#include <ctime>
#include <cstdlib>
#include "GameUI.h"

class Game
{
private:

	SDL_Window* window;
	SDL_Renderer* render;
	std::list<Astroid*> astroids;
	bool isrunning = true;
	Uint32 lastFrameTime;
	Astroid* astroid;
	GameUI* gameU;
	Player* player;
	Enemy* enemy;
	std::list<Enemy*> enemies;
	int lives = 3;
	int score;

public:

	Game();
	~Game();
	void run();
	void Render();
	void handledEvents();
	void spawnAsteroid();
	void SpawnEnemy();
	void scoreAdded(int earned);
	void lifeLost(int lives);
	void Update(float DeltaTime);
	bool isColliding(SDL_Rect a, SDL_Rect b);
	void Destroy();
};

