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

    int lives = 3;
    int speed;
    bool active;
    SDL_Texture* texture;  // Texture for the player
    SDL_Texture* bullets;
    std::string imagePath;
    std::string bulletTexture;
  

public:

    SDL_Rect rect;
    std::list<SDL_Rect> bullet;
    bool invulnerable;          // To track invulnerability state.
    float invulnerabilityTime;  // Time remaining for invulnerability.
    const float maxInvulnerabilityTime = 2.0f;
    Player(SDL_Renderer* renderer, const std::string& filepath);
    ~Player();
    void handleEvent(SDL_Event& event);
    void update(float DeltaTime);
    SDL_Rect GetRect() const;
    void render(SDL_Renderer* renderer);
    bool isActive() const;
    void setInvulnerable();
    void Load(const std::string& filepath);
    void Destroy();
};

#endif