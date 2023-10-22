#include "EnemyBullet.h"
#include <iostream>

int EnemyBullet::nextID = 0;

EnemyBullet::EnemyBullet(SDL_Renderer* renderer, const std::string& bulletTexture, int x, int y)
    : posX(x), posY(y), hasCollided(false) {
   
    
    id = nextID++;
   

    IMG_Init(IMG_INIT_PNG);
   
     Load(bulletTexture);
  
	texture = IMG_LoadTexture(renderer, bulletTexturePath.c_str());


    if (!texture) {
        std::cout << "Error loading bullet textures: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);


    rect.x = posX;
    rect.y = posY;
}

EnemyBullet::~EnemyBullet() {

    SDL_DestroyTexture(texture);


}


void EnemyBullet::Move(int distX, int distY) {

    rect.x += distX;
    rect.y += distY;

}

void EnemyBullet::UpdatePosition(float deltaTime) {
    posY += speed * deltaTime;
    rect.y = posY;
}

int EnemyBullet::getID() const {
    

    return id; }

void EnemyBullet::collided() {

    hasCollided = true;

}

bool EnemyBullet::hasAlreadyCollided() const {
    return hasCollided;
}

void EnemyBullet::Render(SDL_Renderer* renderer) {

    SDL_Rect dstRect = { (int)posX, (int)posY, BULLET_WIDTH, BULLET_HEIGHT };
    try {
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    }
    catch(const char* e){
        std::cout << "Caught an exception: " << e << std::endl;
    }

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

    speed = bulletSpeedY;

}