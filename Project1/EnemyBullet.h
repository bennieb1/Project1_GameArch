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
	std::string bulletTexturePath;
	SDL_Renderer* render;
	float bulletSpeedX;
	float bulletSpeedY;
	float BULLET_HEIGHT = 10.0f;
	float BULLET_WIDTH = 10.0f;
	bool hasCollided;
	static int nextID;  // This will be our ID generator
	int id;

public:
	bool active = true;
	float bulletWidth;
	float bulletHeight;
	bool isBullet;
	SDL_Rect rect;
	float posY;
	float posX;
	float speed;

	void collided();
	bool hasAlreadyCollided() const;
	EnemyBullet(SDL_Renderer* renderer, const std::string& texturePath, int x, int y);
	~EnemyBullet();
	void UpdatePosition(float deltaTime);
	int getID() const;
	void Move(int distX, int distY);
	void Render(SDL_Renderer* rend);
	SDL_Rect GetRect() const;
	void Load( const std::string& filepath);

};

#endif