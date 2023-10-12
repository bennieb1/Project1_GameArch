#include "Player.h"
#include <iostream>


Player::Player(SDL_Renderer* renderer, const  std::string& imagePath, const std::string& bulletTexture) {
    // Initialize rect, lives, etc.
    rect.x = 400; // Example initialization
    rect.y = 300;
    rect.w = 50;
    rect.h = 50;
    lives = 3;
    speed = 10;

    // Load the texture using SDL_image
    texture = IMG_LoadTexture(renderer, imagePath.c_str());
    if (!texture) {
        // Log error or handle failure
        SDL_Log("Failed to load texture: %s", IMG_GetError());
    }
    bullets = IMG_LoadTexture(renderer, bulletTexture.c_str());  // Load bullet texture
    if (!bullets) {
        SDL_Log("Failed to load bullet texture: %s", IMG_GetError());
    }
}

Player::~Player() {
    SDL_DestroyTexture(texture);
}

void Player::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_w: rect.y -= speed; break;
        case SDLK_s: rect.y += speed; break;
        case SDLK_a: rect.x -= speed; break;
        case SDLK_d: rect.x += speed; break;
        case SDLK_SPACE:
            bullet.push_back({ rect.x + rect.w / 2, rect.y, 5, 10 });
            break;
        }
    }
   
}

void Player::update(float DeltaTime) {
    for (auto& bulletRect : bullet) {
        bulletRect.y -= 10;  // Move bullets upwards by 10 pixels
    }
}

void Player::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    for (const auto& bulletRect : bullet) {
        SDL_RenderCopy(renderer, bullets, NULL, &bulletRect);
    }
}
