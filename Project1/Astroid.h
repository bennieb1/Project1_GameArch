#pragma once
#ifndef ASTEROID_H
#define ASTEROID_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <list>
#include <fstream>
#include "json.hpp"

class Astroid
{

private:

	SDL_Rect rect;
	SDL_Texture* astroid;

	std::string astroidPath;
	float postX;
	float postY;
	float speedX;
	float speedY;

public:

	Astroid(SDL_Renderer* render, const std::string& astroidPath);
	~Astroid();

	void Update(float TimeDelta);
	void Render(SDL_Renderer* rend);
	SDL_Rect GetRect();
	void Load(const std::string& filepath);



};

#endif

