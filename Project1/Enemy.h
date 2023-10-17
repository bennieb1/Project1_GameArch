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
    SDL_Renderer* renderer;
    std::list<Enemy*> bullets;
    float speedY;
    int health;
    float positionX;
    float positionY;
    const int SCREEN_WIDTH = 1280;  
    const int SCREEN_HEIGHT = 720;
    const int bulletSpeed = 10;
    bool isBullet = false;
  


public:
    Enemy(SDL_Renderer* renderer, const std::string& texturePath, int initHealth = 100);
    ~Enemy();

    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);
    void Move(int distX, int distY);
    void SetRandomTopPosition();
    bool isColliding(SDL_Rect centerA, SDL_Rect centerB);
    void TakeDamage(int damage);
     bool OnBulletHit();
     void UpdateAndRenderBullets();
     void Shoot();
     void UpdatePositionRandomly(float deltaTime);
     
   void Load(const std::string& filepath) ;
    SDL_Rect GetRect() const;

private:
    bool LoadTexture(SDL_Renderer* renderer, const std::string& filepath);
};

#endif

