#pragma once
#ifndef GAMEUI_H
#define GAMEUI_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>


class GameUI
{

private:
	TTF_Font* Font;
	int score;
	int highScore;
	int lives;

public:

	GameUI(const std::string& fontPath);
	~GameUI();
	void setScore(int newScore);
	void ScoreAdded(int points);
	void setLife(int life);
	void Render(SDL_Renderer* rend);


};

#endif

