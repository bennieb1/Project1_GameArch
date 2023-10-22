#include "Enemy.h"
#include "Game.h"



Enemy::Enemy(SDL_Renderer* renderer, const std::string& texturePath, int initHealth)
    :  posX(x), posY(y), speed(speed), isBullet(false), bulletSpeed(-500) {
    health = initHealth;

 



    IMG_Init(IMG_INIT_PNG);
  
    Load(texturePath);
    texture = IMG_LoadTexture(renderer, imagePath.c_str());
    if (!texture) {
        std::cout << "Error loading enemy textures: " << SDL_GetError() << std::endl;
        return;
    }
   
    render = renderer;
    std::cout << bulletTexture.c_str() << std::endl;

    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);


    rect.x = 700 - rect.w / 2;
    rect.y = 100 - rect.h / 2;
}


Enemy::~Enemy() {
    SDL_DestroyTexture(texture);
    delete bullet;
}




void Enemy::Update(float DeltaTime) {


}

void Enemy::Render(SDL_Renderer* renderer) {
   
  
    
    SDL_RenderCopy(renderer, texture, NULL, &rect);
 
    
  
}


bool Enemy::isColliding(SDL_Rect centerA, SDL_Rect centerB) {
    float distx = centerA.x + centerA.w / 2 - (centerB.x + centerB.w / 2);  
    float disty = centerA.y + centerA.h / 2 - (centerB.y + centerB.h / 2);
    float distance = sqrt(distx * distx + disty * disty);

    float radiusA = centerA.w / 2;
    float radiusB = centerB.w / 2;

    return distance <= (radiusA + radiusB);
}

void Enemy::TakeDamage(int damage) {
    health -= damage;
    if (health <= 0) {

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
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastBulletShotTime > bulletCooldown) {
    EnemyBullet* newBullet = new EnemyBullet(render, "EnemyBulletA.JSON", rect.x + rect.w / 2, rect.y); // 0 health because it's a bullet
    newBullet->isBullet = true;
    newBullet->rect.w= 20; 
    newBullet->rect.h= 20;
    newBullet->rect.x = rect.x + rect.w / 2 - newBullet->rect.w / 2;
    newBullet->rect.y = rect.y;
    bullets.push_back(newBullet);


    lastBulletShotTime = currentTime;
    }
}


void Enemy::setBulletsList(std::list<EnemyBullet*>& gameBullets) {
    bulletss = &gameBullets;
}

void Enemy::RenderBullets(SDL_Renderer* renderer) {
    
 
    for (auto& bullet : bullets) {

        bullet->Render(render);
    }
}

void Enemy::UpdateBullets(float deltaTime) {
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        (*it)->UpdatePosition(deltaTime);  
        if ((*it)->posY > SCREEN_HEIGHT) {  
            delete* it;
            it = bullets.erase(it);
        }
        else {
            ++it;
        }
    }
}

std::list<EnemyBullet*>& Enemy::getBullets() {
    return bullets;
}
void Enemy::UpdatePosition(float deltaTime) {
    posY += speed * deltaTime;
}

SDL_Rect Enemy::GetRect() const {
    return rect;
}
void Enemy::SetRandomTopPosition() {
    rect.x = rand() % (SCREEN_WIDTH - rect.w); 
    rect.y = -rect.h; 
}

void Enemy::UpdatePositionRandomly(float deltaTime) {
 

    float minX = -5; 
    float maxX = 5;
    float minY = 10; 
    float maxY = 700; 

    rect.x += (rand() % (int)((maxX - minX) + 1) + minX) * deltaTime; 
    float downwardSpeed = 200; 
    rect.y += downwardSpeed * deltaTime;


    if (rect.x < 0) rect.x = 0;
    if (rect.x + rect.w > SCREEN_WIDTH) rect.x = SCREEN_WIDTH - rect.w;

    if (rect.y + rect.h > SCREEN_HEIGHT) {
        rect.y = -rect.h;
        rect.x = rand() % (SCREEN_WIDTH - rect.w);
    }
    if (isBullet) {
      
        rect.y += bulletSpeed * deltaTime;
    }
    else {
    
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


   
}