#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


class Player
{
private:
    SDL_Rect rect;
    int lives;
    SDL_Texture* texture;  // Texture for the player

public:
    Player(SDL_Renderer* renderer, const std::string& imagePath);
    ~Player();
    void handleEvent(SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);

};

#endif