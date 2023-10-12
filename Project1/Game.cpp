#include "Game.h"

Game::Game() {
    SDL_Init(SDL_INIT_VIDEO);
    if (TTF_Init() == -1) { // Initialize SDL2_ttf
        SDL_Log("Unable to initialize SDL2_ttf: %s", TTF_GetError());
        // You may choose to exit or handle this error appropriately.
    }

    window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1240, 720, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, 0);

    isrunning = true;
    lastFrameTime = SDL_GetTicks();
    gameU = new GameUI("resources\\Hud\\cour.ttf");

    player = new Player(render, std::string("resources\\Mainplayer\\player.png"), std::string("resources\\Mainplayer\\laserGreen.png"));
      // Assuming Player takes a texture in its constructor

}
Game::~Game() {
    // ... cleanup other resources ...
    delete gameU;
    delete player;
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    IMG_Quit();  // If you initialized SDL_image
    SDL_Quit();
}
void Game::Render() {
    SDL_RenderClear(render);

    player->render(render);

    for (auto& asteroid : astroids) {
        asteroid->Render(render);
    }
    
    gameU->Render(render); // Render the game UI
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
        SDL_Delay(16);   // Cap at 60fps for now
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
   
    Astroid* newAsteroid = new Astroid(render, "resources\\Asteroids\\meteorBig.png");
    astroids.push_back(newAsteroid);

    Astroid* newAsteroids = new Astroid(render, "resources\\Asteroids\\meteorSmall.png");
    astroids.push_back(newAsteroids);




}
void Game::scoreAdded(int earned) {
  
    gameU->ScoreAdded(earned);

}
void Game::lifeLost(int lives) {

    
    lives--;  // Assuming lives is in the Game class
   
    gameU->setLife(lives);
}

void Game::Update(float DeltaTime) {
    player->update(DeltaTime);

    for (auto& asteroid : astroids) {
        asteroid->Update(DeltaTime);
    }
}

void Game::Destroy() {
    delete player;
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}