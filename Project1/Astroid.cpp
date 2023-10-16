#include "Astroid.h"

#include <cstdlib>
#include <iostream>

Astroid::Astroid(SDL_Renderer* render, const std::string& filepath) {

    postX = 600;
    postY = 10;
    IMG_Init(IMG_INIT_PNG);
    Load(filepath);

    astroid = IMG_LoadTexture(render, astroidPath.c_str());
    if (!astroid) {
        std::cout << "Error loading asteroid surface: " << SDL_GetError() << std::endl;
        return;
    }


    SDL_QueryTexture(astroid, NULL, NULL, &rect.w, &rect.h);

    postX = rand() % (1240 - rect.w);
    postY = -15;

    if (!astroid) {
        std::cout << "Error creating asteroid texture: " << SDL_GetError() << std::endl;
        return;
    }


    speedX = 0.0f;
    speedY = 150.0f;
}

Astroid::~Astroid() {
    SDL_DestroyTexture(astroid);
}

void Astroid::Update(float TimeDelta) {
    postX += speedX * TimeDelta;
    postY += speedY * TimeDelta;
}

void Astroid::Render(SDL_Renderer* renderer) {
    rect.x = postX;
    rect.y = postY;
    SDL_RenderCopy(renderer, astroid, NULL, &rect);

}

SDL_Rect Astroid::GetRect() {
    rect.x = postX;
    rect.y = postY;
    return rect;
}

void Astroid::Load(const std::string& filepath) {

    std::ifstream inputStream(filepath);
    std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
    json::JSON document = json::JSON::Load(str);

    astroidPath = document["astroid_path"].ToString();
    speedX = document["speed"]["x"].ToFloat();
    speedY = document["speed"]["y"].ToFloat();

}