#pragma once

#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <fstream>
#include "json.hpp"

class EnemyBullet
{

private:

	SDL_Texture* texture;
	SDL_Rect rect;
	std::string bulletTexture;
	std::string bulletTexturePath;

	float bulletSpeedX;
	float bulletSpeedY;
	int bulletWidth;
	int bulletHeight;
public:

	EnemyBullet(SDL_Renderer* renderer, const std::string& texturePath, int x, int y);
	~EnemyBullet();

	void Move(int distX, int distY);
	void Render(SDL_Renderer* rend);
	SDL_Rect GetRect() const;
	void Load( const std::string& filepath);

};

#endif