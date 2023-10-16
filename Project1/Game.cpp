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
      

}
Game::~Game() {
   
    delete gameU;
    delete player;
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