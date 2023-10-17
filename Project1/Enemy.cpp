#include "Enemy.h"



Enemy::Enemy(SDL_Renderer* renderer, const std::string& texturePath, int initHealth)
    :  isBullet(false), bulletSpeed(-500) {
    health = initHealth;



    IMG_Init(IMG_INIT_PNG);
    // Load the enemy texture
    Load(texturePath);
    texture = IMG_LoadTexture(renderer, imagePath.c_str());
    if (!texture) {
        std::cout << "Error loading enemy texture: " << SDL_GetError() << std::endl;
        return;
    }
    bullet = IMG_LoadTexture(renderer, bulletTexture.c_str());
    if (!bullet) {
        SDL_Log("Failed to load bullet texture: %s", IMG_GetError());
    }
    render = renderer;
    std::cout << bulletTexture.c_str() << std::endl;

    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

    // Initial position
    rect.x = 700; // You can change this
    rect.y = 100; // You can change this

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
bool Enemy::OnBulletHit()  {
    TakeDamage(1);
    if (health <= 0) {
        std::cout << "Enemy destroyed!" << std::endl;
        return true;
    }
    return false;
}



void Enemy::Shoot() {
    EnemyBullet* newBullet = new EnemyBullet(render, "EnemyBulletA.JSON", 100,100); // 0 health because it's a bullet
    newBullet->isBullet = true;
    newBullet->rect.x = rect.x + rect.w / 2; // Start from the center of the enemy
    newBullet->rect.y = rect.y;
    bullets.push_back(newBullet);
}


void Enemy::RenderBullets(SDL_Renderer* renderer) {
    for (EnemyBullet* bullet : bullets) {
        bullet->Render(renderer); // Render each bullet
    }
}

SDL_Rect Enemy::GetRect() const {
    return rect;
}
void Enemy::SetRandomTopPosition() {
    rect.x = rand() % (SCREEN_WIDTH - rect.w); // random position between 0 and (SCREEN_WIDTH - width of enemy)
    rect.y = -rect.h; // just above the screen
}

void Enemy::UpdatePositionRandomly(float deltaTime) {
    // Generate random X and Y coordinates within a specified range

    float minX = -5; // Maximum leftward movement
    float maxX = 5;// Maximum X-coordinate
    float minY = 10; // Minimum Y-coordinate
    float maxY = 700; // Maximum Y-coordinate

    rect.x += (rand() % (int)((maxX - minX) + 1) + minX) * deltaTime; // Reduce speed by half
    float downwardSpeed = 200; // This is the speed at which the enemy moves downward. Adjust as needed.
    rect.y += downwardSpeed * deltaTime;

    // Ensure the enemy doesn't move off the left or right of the screen
    if (rect.x < 0) rect.x = 0;
    if (rect.x + rect.w > SCREEN_WIDTH) rect.x = SCREEN_WIDTH - rect.w;

    if (rect.y + rect.h > SCREEN_HEIGHT) {
        rect.y = -rect.h; // Position it just above the screen
        rect.x = rand() % (SCREEN_WIDTH - rect.w); // Randomize the x position
    }
    if (isBullet) {
        // Movement logic for bullet
        rect.y += bulletSpeed * deltaTime;
    }
    else {
        // Existing enemy movement logic...
    }
    
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