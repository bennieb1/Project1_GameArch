#include "Player.h"
#include <iostream>


Player::Player(SDL_Renderer* renderer, const  std::string& imagePath) {
    // Initialize rect, lives, etc.
    rect.x = 400; // Example initialization
    rect.y = 300;
    rect.w = 50;
    rect.h = 50;
    lives = 3;

    // Load the texture using SDL_image
    texture = IMG_LoadTexture(renderer, imagePath.c_str());
    if (!texture) {
        // Log error or handle failure
        SDL_Log("Failed to load texture: %s", IMG_GetError());
    }
}

Player::~Player() {
    SDL_DestroyTexture(texture);
}

void Player::handleEvent(SDL_Event& event) {
    //... [same as previous]
}

void Player::update() {
    //... [same as previous]
}

void Player::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
