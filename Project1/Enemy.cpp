#include "Enemy.h"



Enemy::Enemy(SDL_Renderer* renderer, const std::string& filepath, int initHealth)  {
    health = initHealth;

    IMG_Init(IMG_INIT_PNG);
    // Load the enemy texture
    Load(filepath);
    texture = IMG_LoadTexture(renderer, imagePath.c_str());
    if (!texture) {
        std::cout << "Error loading enemy texture: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

    // Initial position
    rect.x = 500; // You can change this
    rect.y = 200; // You can change this

    positionX = 400;
    positionY = 200;
}


Enemy::~Enemy() {
    SDL_DestroyTexture(texture);
}

void Enemy::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}



bool Enemy::isColliding(SDL_Rect centerA, SDL_Rect centerB) {
    float distx = centerA.x + centerA.w / 2 - (centerB.x + centerB.w / 2);  // Adjusting to get the center of rects
    float disty = centerA.y + centerA.h / 2 - (centerB.y + centerB.h / 2);
    float distance = sqrt(distx * distx + disty * disty);

    float radiusA = centerA.w / 2;
    float radiusB = centerB.w / 2;

    return distance <= (radiusA + radiusB);
}

void Enemy::TakeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        // Handle enemy destruction here, or set a flag to handle it elsewhere
        std::cout << "Enemy destroyed!" << std::endl;
    }
    else {
        std::cout << "Enemy health: " << health << std::endl;
    }
}
void Enemy::OnBulletHit()  {
    TakeDamage(1);
    if (health <= 0) {
     
    }
}SDL_Rect Enemy::GetRect() const {
    return rect;
}

void Enemy::UpdatePositionRandomly(float deltaTime) {
    // Generate random X and Y coordinates within a specified range

    float minX = 10; // Minimum X-coordinate
    float maxX = 900; // Maximum X-coordinate
    float minY = 10; // Minimum Y-coordinate
    float maxY = 700; // Maximum Y-coordinate

    rect.x += (rand() % (int)((maxX - minX) + 1) + minX) * deltaTime * 0.5f; // Reduce speed by half
    rect.y += (rand() % (int)((maxY - minY) + 1) + minY) * deltaTime * 0.5f; // Reduce speed by half

    
}

void Enemy::Load(const std::string& filepath) {

  
    std::ifstream inputStream(filepath);
    std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
    json::JSON document = json::JSON::Load(str);


    rect.x = document["initial_position"]["x"].ToInt();
    rect.y = document["initial_position"]["y"].ToInt();
    rect.w = document["size"]["width"].ToInt();
    rect.h = document["size"]["height"].ToInt();
    imagePath = document["image_path"].ToString();
    bulletTexture = document["bullet_texture"].ToString();

   
}