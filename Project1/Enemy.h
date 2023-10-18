#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "json.hpp"
#include <fstream>
#include "EnemyBullet.h"
#include <list>


class Enemy  {
private:
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Texture* bullet;
    std::list<SDL_Rect> bulleta;
    std::string imagePath;
    std::string bulletTexture;
    SDL_Renderer* render;
   // std::list<EnemyBullet*> bullets;
    std::list<Enemy*>enemy;
    std::list<EnemyBullet*>* bulletss = nullptr;
    float speedY;
    int health;
    float positionX;
    float positionY;
    float x;
    float y;
    const int SCREEN_WIDTH = 1280;  
    const int SCREEN_HEIGHT = 720;
    const int bulletSpeed;
    bool isBullet = true;
    Uint32 lastBulletShotTime = 0;
    Uint32 bulletCooldown = 1500; // 1 second cooldown

  


public:
    Enemy(SDL_Renderer* renderer, const std::string& texturePath, int initHealth = 100);
    ~Enemy();
   std::list<EnemyBullet*> bullets;
    /*int bulletWidth;
    int bulletHeight;*/
    float posY;
    float posX;
    float speed;

    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);
    void Move(int distX, int distY);
    void SetRandomTopPosition();
    bool isColliding(SDL_Rect centerA, SDL_Rect centerB);
    void TakeDamage(int damage);
     bool OnBulletHit();
     void Shoot();
     void RenderBullets(SDL_Renderer* renderer);
     void setBulletsList(std::list<EnemyBullet*>& gameBullets);
     void UpdatePosition(float deltaTime);
     void UpdateBullets(float deltaTime);
     void UpdatePositionRandomly(float deltaTime);
     std::list<EnemyBullet*>& getBullets();
   void Load(const std::string& filepath) ;
    SDL_Rect GetRect() const;

private:
    bool LoadTexture(SDL_Renderer* renderer, const std::string& filepath);
};

#endif

