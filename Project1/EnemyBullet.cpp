#include "EnemyBullet.h"
#include <iostream>


EnemyBullet::EnemyBullet(SDL_Renderer* renderer, const std::string& bulletTexturePath, int x, int y) {
    

    IMG_Init(IMG_INIT_PNG);
   
  
	texture = IMG_LoadTexture(renderer, bulletTexturePath.c_str());


    if (!texture) {
        std::cout << "Error loading bullet texture: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);


    rect.x = x - rect.w / 2; // So the bullet appears centered on x
    rect.y = y;
}

EnemyBullet::~EnemyBullet() {

    SDL_DestroyTexture(texture);


}


void EnemyBullet::Move(int distX, int distY) {

    rect.x += distX;
    rect.y += distY;

}

void EnemyBullet::Render(SDL_Renderer* renderer) {

    SDL_RenderCopy(renderer, texture, NULL, &rect);


}

SDL_Rect EnemyBullet::GetRect() const {
    return rect;
}
void EnemyBullet::Load(const std::string& filepath) {

    std::ifstream inputStream(filepath);
    std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
    json::JSON document = json::JSON::Load(str);

    bulletTexturePath = document["bullet_texture"].ToString();
    bulletSpeedX = document["speed"]["x"].ToFloat();
    bulletSpeedY = document["speed"]["y"].ToFloat();
    bulletWidth = document["size"]["width"].ToInt();
    bulletHeight = document["size"]["height"].ToInt();

}