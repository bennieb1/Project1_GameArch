#include "Astroid.h"

#include <cstdlib>
#include <iostream>

Astroid::Astroid(SDL_Renderer* render, const std::string& astroidPath) {

    postX = 600;  
    postY = 10;
    IMG_Init(IMG_INIT_PNG);
   

     SDL_Surface* asteroidSurface = IMG_Load(astroidPath.c_str());
    if (!asteroidSurface) {
        std::cout << "Error loading asteroid surface: " << SDL_GetError() << std::endl;
        return;
    }

    astroid = SDL_CreateTextureFromSurface(render, asteroidSurface);
    SDL_QueryTexture(astroid, NULL, NULL, &rect.w, &rect.h);
    SDL_FreeSurface(asteroidSurface);
    postX = rand() % (1240 - asteroidSurface->w);
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