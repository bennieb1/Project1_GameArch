#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include "json.hpp"


class Player
{
private:
    SDL_Rect rect;
    int lives;
    int speed;
    SDL_Texture* texture;  // Texture for the player
    SDL_Texture* bullets;
    std::list<SDL_Rect> bullet;    
    std::string imagePath;
    std::string bulletTexture;

public:
    Player(SDL_Renderer* renderer, const std::string& filepath);
    ~Player();
    void handleEvent(SDL_Event& event);
    void update(float DeltaTime);
    void render(SDL_Renderer* renderer);
    void Load(const std::string& filepath);

};

#endif