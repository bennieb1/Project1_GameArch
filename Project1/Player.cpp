#include "Player.h"
#include <iostream>


Player::Player(SDL_Renderer* renderer, const std::string& filepath) {
    
    Load(filepath);
   
    texture = IMG_LoadTexture(renderer, imagePath.c_str());
    if (!texture) {
       
        SDL_Log("Failed to load texture: %s", IMG_GetError());
    }
    bullets = IMG_LoadTexture(renderer, bulletTexture.c_str());  
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
        bulletRect.y -= 10;  
    }
}

void Player::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    for (const auto& bulletRect : bullet) {
        SDL_RenderCopy(renderer, bullets, NULL, &bulletRect);
    }
}

void Player::Load(const std::string& filepath) {


    std::ifstream inputStream(filepath);
    std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
    json::JSON document = json::JSON::Load(str);


    rect.x = document["initial_position"]["x"].ToInt();
    rect.y = document["initial_position"]["y"].ToInt();
    rect.w = document["size"]["width"].ToInt();
    rect.h = document["size"]["height"].ToInt();
    lives = document["lives"].ToInt();
    speed = document["speed"].ToInt();
    imagePath = document["image_path"].ToString();
    bulletTexture = document["bullet_texture"].ToString();


}
