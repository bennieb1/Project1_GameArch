#include "Game.h"

Game::Game() {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1240, 720, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, 0);

    isrunning = true;

 

    player = new Player(render, std::string("C:\\Users\\bennieb\\Documents\\GameArchitecture\\Project1\\Project1\\prog50049.project1.resources\\Mainplayer\\player.png"));
      // Assuming Player takes a texture in its constructor

}
Game::~Game() {
    // ... cleanup other resources ...
    delete player;
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    IMG_Quit();  // If you initialized SDL_image
    SDL_Quit();
}
void Game::Render() {
 
    SDL_RenderClear(render);

  
    
    player->render(render);
 

    SDL_RenderPresent(render);

   
}