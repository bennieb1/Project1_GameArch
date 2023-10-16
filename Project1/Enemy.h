#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "json.hpp"
#include <fstream>


class Enemy  {
private:
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Texture* bullets;
    std::string imagePath;
    std::string bulletTexture;
    float speedY;
    int health;
    float positionX;
    float positionY;

public:
    Enemy(SDL_Renderer* renderer, const std::string& filepath, int initHealth);
    ~Enemy();

    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);

 
    bool isColliding(SDL_Rect centerA, SDL_Rect centerB);
    void TakeDamage(int damage);
     void OnBulletHit();
     void UpdatePositionRandomly(float deltaTime);
     float GetPositionX() const { return positionX; }
     float GetPositionY() const { return positionY; }
   void Load(const std::string& filepath) ;
    SDL_Rect GetRect() const;

private:
    bool LoadTexture(SDL_Renderer* renderer, const std::string& filepath);
};

#endif

