#include "Game.h"

Game::Game() {
    SDL_Init(SDL_INIT_VIDEO);
    if (TTF_Init() == -1) {
        SDL_Log("Unable to initialize SDL2_ttf: %s", TTF_GetError());

    }

    window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1240, 720, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, 0);

    isrunning = true;
    lastFrameTime = SDL_GetTicks();
    gameU = new GameUI("resources\\Hud\\cour.ttf");

    player = new Player(render, "player.JSON");

   // enemies.push_back(new Enemy(render, "EnemyA.JSON", 3));
   // enemies.push_back(new Enemy(render, "EnemyB.JSON", 5));

    Enemy* newEnemy = new Enemy(render, "EnemyA.JSON", 3 );
    newEnemy->SetRandomTopPosition();
    enemies.push_back(newEnemy);

    Enemy* newerEnemy = new Enemy(render, "EnemyB.JSON", 5 );
    newerEnemy->SetRandomTopPosition();
    enemies.push_back(newerEnemy);
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

    player->render(render);

    for (auto& asteroid : astroids) {
        asteroid->Render(render);
    }

    for (auto& e : enemies) {
        e->Render(render);
       // e->Render(render); // This renders the enemy
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
            nextSpawnTime = currentFrameTime + 2000;  // Schedule the next spawn in 5 seconds
        }
        handledEvents();
        Update(deltaTime);
        Render();
       // SpawnEnemy();


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

//void Game::SpawnEnemy() {
//
//    Enemy* newEnemy = new Enemy(render, "EnemyA.JSON", 3);
//    newEnemy->SetRandomTopPosition();
//    enemies.push_back(newEnemy);
//
//    Enemy* newerEnemy = new Enemy(render, "EnemyB.JSON", 5);
//    newerEnemy->SetRandomTopPosition();
//    enemies.push_back(newerEnemy);
//
//}

void Game::scoreAdded(int earned) {

    gameU->ScoreAdded(earned);

}
void Game::lifeLost(int livesLost) {
    std::cout << "lifeLost called. Current lives: " << lives << ", Lives to lose: " << livesLost << std::endl;

    lives -= livesLost;
    if (lives <= 0) {
        lives = 3; // This will reset the game every time. You may want a game over state.
        score = 0;  // Reset score to 0
        gameU->setScore(score); // ... rest of your code ...
    }
    player->Destroy();

    gameU->setLife(lives);
}

void Game::Update(float DeltaTime) {
    player->update(DeltaTime);


    for (auto it = astroids.begin(); it != astroids.end();) {
        if (isColliding(player->rect, (*it)->GetRect()) && !player->invulnerable) {
            std::cout << "Collision detected!" << std::endl;
            lifeLost(1);
            player->setInvulnerable();
            delete* it;
            it = astroids.erase(it);  // Remove the asteroid from the list
            break;  // Exit the loop after handling the collision
        }
        else {
            ++it;
        }
    }

   

    for (auto& enemy : enemies) {
        enemy->Render(render); // This renders the enemy
        enemy->Shoot();
        // This updates and renders the bullets for each enemy
    }
   
    for (auto& enemy : enemies) {
        enemy->UpdatePositionRandomly(DeltaTime);
        // Check collisions and other logic specific to each enemy
      
    }


    for (auto& bullet : player->bullet) {
        for (auto it = astroids.begin(); it != astroids.end();) {
            if (isColliding(bullet, (*it)->GetRect())) {
                // Bullet hits asteroid
                scoreAdded(10);  // 10 points for each asteroid hit
                delete* it;  // Free the asteroid's memory
                it = astroids.erase(it);  // Remove the asteroid from the list
            }
            else {
                ++it;
            }
        }
    }
    for (auto& asteroid : astroids) {
        asteroid->Update(DeltaTime);
    }

    for (auto bulletIt = player->bullet.begin(); bulletIt != player->bullet.end(); ) {
        bool bulletDeleted = false;

        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
            if (isColliding(*bulletIt, (*enemyIt)->GetRect())) {
                bool isEnemyDestroyed = (*enemyIt)->OnBulletHit();
                bulletIt = player->bullet.erase(bulletIt);
                bulletDeleted = true;

                if (isEnemyDestroyed) {
                    scoreAdded(50);
                    delete* enemyIt;  // Delete the enemy
                    enemyIt = enemies.erase(enemyIt);
                    destroyedEnemies++;
                }
                else {
                    ++enemyIt;
                }
                break;  // break out of the enemy loop if a bullet hit an enemy
            }
            else {
                ++enemyIt;
            }
        }

        if (!bulletDeleted) {
            ++bulletIt;
        }
    }

    // Then, check collisions between player and enemies
    for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
        if (isColliding(player->GetRect(), (*enemyIt)->GetRect())) {
            // Handle the collision. This could be player health decrease, game over logic, etc.
            lifeLost(1);
            scoreAdded(50);

            delete* enemyIt;
            enemyIt = enemies.erase(enemyIt);
            destroyedEnemies++;
        }
        else {
            ++enemyIt;
        }
    }

    // Finally, check if 2 enemies have been destroyed and respawn new ones
    if (destroyedEnemies == 2) {
        // Reset the counter
        destroyedEnemies = 0;

        // Spawn 2 new enemies
        Enemy* newEnemy1 = new Enemy(render, "EnemyA.JSON", 3 );
        newEnemy1->SetRandomTopPosition();
        enemies.push_back(newEnemy1);

        Enemy* newEnemy2 = new Enemy(render, "EnemyB.JSON", 5);
        newEnemy2->SetRandomTopPosition();
        enemies.push_back(newEnemy2);
    }



  
}

bool Game::isColliding(SDL_Rect centerA, SDL_Rect centerB) {
    float distx = centerA.x + centerA.w / 2 - (centerB.x + centerB.w / 2);  // Adjusting to get the center of rects
    float disty = centerA.y + centerA.h / 2 - (centerB.y + centerB.h / 2);
    float distance = sqrt(distx * distx + disty * disty);

    float radiusA = centerA.w / 2;
    float radiusB = centerB.w / 2;

    return distance <= (radiusA + radiusB);
}
void Game::Destroy() {
    delete player;
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}