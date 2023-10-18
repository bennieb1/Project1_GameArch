#include "Game.h"

Game::Game() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    if (TTF_Init() == -1) {
        SDL_Log("Unable to initialize SDL2_ttf: %s", TTF_GetError());

    }


    window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1240, 720, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, 0);

    isrunning = true;
    lastFrameTime = SDL_GetTicks();

    Load("BackGround.JSON");

    std::cout << "file retrived:" << background << std::endl;

    SDL_Surface* tempSurface = IMG_Load(background.c_str());
    if (tempSurface == nullptr) {
        SDL_Log("Unable to load image %s! SDL_image Error: %s\n", background.c_str(), IMG_GetError());
        return;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(render, tempSurface);
    SDL_FreeSurface(tempSurface);


    gameU = new GameUI("resources\\Hud\\cour.ttf");

    player = new Player(render, "player.JSON");


    Enemy* newEnemy = new Enemy(render, "EnemyA.JSON", 3 );
    newEnemy->SetRandomTopPosition();
    enemies.push_back(newEnemy);
    newEnemy->setBulletsList(bullets);

    Enemy* newerEnemy = new Enemy(render, "EnemyB.JSON", 5 );
    newerEnemy->SetRandomTopPosition();
    enemies.push_back(newerEnemy);
    newerEnemy->setBulletsList(bullets);
}
Game::~Game() {

    delete gameU;
    delete player;

    for (auto& enemy : enemies) {
        delete enemy;
    }
   SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
void Game::Render() {
    SDL_RenderClear(render);


    
        SDL_RenderCopy(render, backgroundTexture, NULL, NULL);
   

    player->render(render);

    for (auto& asteroid : astroids) {
        asteroid->Render(render);
    }


    for (auto& e : enemies) {
        e->Render(render);
   
        e->RenderBullets(render);
        e->Shoot();
    }


    gameU->Render(render);
    SDL_RenderPresent(render);


}

void Game::run() {

    Uint32 nextSpawnTime = SDL_GetTicks() + 2000;
    while (isrunning) {
        Uint32 currentFrameTime = SDL_GetTicks();
        float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;


        if (currentFrameTime >= nextSpawnTime) {
            spawnAsteroid();
            nextSpawnTime = currentFrameTime + 2000;  
        }
        handledEvents();
        Update(deltaTime);
        Render();
       
        gatherEnemyBullets();


        for (auto& enemy : enemies) {
            enemy->UpdateBullets(deltaTime);
            enemy->RenderBullets(render);
        }


        lastFrameTime = currentFrameTime;
        SDL_Delay(16);
    }
}
void Game::handledEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            isrunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isrunning = false;
                break;
            }
        default:
            player->handleEvent(event);
            break;
        }
    }
}
void Game::spawnAsteroid() {

    Astroid* newAsteroid = new Astroid(render, "meteorSmall.JSON");
    astroids.push_back(newAsteroid);

    Astroid* newAsteroids = new Astroid(render, "metorBig.JSON");
    astroids.push_back(newAsteroids);




}




void Game::gatherEnemyBullets()
{
    for (auto enemy : enemies)
    {
        std::list<EnemyBullet*> enemyBullets = enemy->getBullets();
        bullets.insert(bullets.end(), enemyBullets.begin(), enemyBullets.end());
    }
}



void Game::scoreAdded(int earned) {

    gameU->ScoreAdded(earned);

}
void Game::lifeLost(int livesLost) {
    std::cout << "lifeLost called. Current lives: " << lives << ", Lives to lose: " << livesLost << std::endl;

    lives -= livesLost;
    if (lives <= 0) {
        lives = 3;
        score = 0;  
        gameU->setScore(score); 
    }
    player->Destroy();

    gameU->setLife(lives);
}

void Game::Update(float DeltaTime) {
    player->update(DeltaTime);


    for (auto it = astroids.begin(); it != astroids.end();) {
        if (isColliding(player->rect, (*it)->GetRect()) && !player->invulnerable) {
            std::cout << "Collision detected!" << std::endl;

            player->StartFlashing();
            lifeLost(1);
            player->setInvulnerable();
            delete* it;
            it = astroids.erase(it); 
            break;  
        }
        else {
            ++it;
        }
    }



    for (auto& enemy : enemies) {
        enemy->UpdatePositionRandomly(DeltaTime);
    
        enemy->Render(render);
        enemy->UpdateBullets(DeltaTime);
        enemy->RenderBullets(render);
        enemy->Shoot();
    }


    for (auto& bullet : player->bullet) {
        for (auto it = astroids.begin(); it != astroids.end();) {
            if (isColliding(bullet, (*it)->GetRect())) {
               
               
                scoreAdded(10);
                delete* it;  // Free the asteroid's memory
                it = astroids.erase(it);
            }
            else {
                ++it;
            }
        }
    }
    for (auto& asteroid : astroids) {
        asteroid->Update(DeltaTime);
    }



    for (auto bulletss = bullets.begin(); bulletss != bullets.end(); ++bulletss) {
        if ((*bulletss)->active && !(*bulletss)->hasAlreadyCollided()) {
            if (isColliding(player->GetRect(), (*bulletss)->GetRect())) {
                std::cout << "Collision detected!" << std::endl;
                lifeLost(1);
                player->StartFlashing();
               // player->setInvulnerable();
                (*bulletss)->collided();
                (*bulletss)->active = false;
            }
        }
    }

    for (auto bulletIt = player->bullet.begin(); bulletIt != player->bullet.end(); ) {
        bool bulletDeleted = false;

        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
            if (isColliding(*bulletIt, (*enemyIt)->GetRect())) {
                bool isEnemyDestroyed = (*enemyIt)->OnBulletHit();
                bulletIt = player->bullet.erase(bulletIt);
                bulletDeleted = true;
               // player->StartFlashing();
                if (isEnemyDestroyed) {
                    scoreAdded(50);
                    delete* enemyIt;  // Delete the enemy
                    enemyIt = enemies.erase(enemyIt);
                    destroyedEnemies++;
                }
                else {
                    ++enemyIt;
                }
                break;
            }
            else {
                ++enemyIt;
            }
        }

        if (!bulletDeleted) {
            ++bulletIt;
        }
    }


    for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
        if (isColliding(player->GetRect(), (*enemyIt)->GetRect())) {

            lifeLost(1);
            scoreAdded(50);
            player->StartFlashing();
            player->setInvulnerable();
            delete* enemyIt;
            enemyIt = enemies.erase(enemyIt);
            destroyedEnemies++;
        }
        else {
            ++enemyIt;
        }
    }


    if (destroyedEnemies == 2) {

        destroyedEnemies = 0;


        Enemy* newEnemy1 = new Enemy(render, "EnemyA.JSON", 3);
        newEnemy1->SetRandomTopPosition();
        enemies.push_back(newEnemy1);

        Enemy* newEnemy2 = new Enemy(render, "EnemyB.JSON", 5);
        newEnemy2->SetRandomTopPosition();
        enemies.push_back(newEnemy2);
    }

}

bool Game::isColliding(SDL_Rect centerA, SDL_Rect centerB) {
    float distx = centerA.x + centerA.w / 2 - (centerB.x + centerB.w / 2);  
    float disty = centerA.y + centerA.h / 2 - (centerB.y + centerB.h / 2);
    float distance = sqrt(distx * distx + disty * disty);

    float radiusA = centerA.w / 2;
    float radiusB = centerB.w / 2;

    return distance <= (radiusA + radiusB);
}

void Game::Load(const std::string& filepath) {

    std::ifstream inputStream(filepath);
    std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
    json::JSON document = json::JSON::Load(str);

    background = document["background_path"].ToString();


}

void Game::Destroy() {
    delete player;
    delete astroid;
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}