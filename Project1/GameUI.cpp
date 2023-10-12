#include "GameUI.h"

GameUI::GameUI(const std::string& fontPath) {

	Font = TTF_OpenFont(fontPath.c_str(), 24);
	if (!Font) {
		SDL_Log("Failed to load font: %s", TTF_GetError());
	}
	score = 0;
	highScore = 0;
	lives = 5;

}

GameUI::~GameUI() {
	TTF_CloseFont(Font);
}


void GameUI::ScoreAdded(int points) {

	score += points;

	if (score > highScore) {
	
		highScore = score;

	}

}

void GameUI::setLife(int life) {

	lives = life;


}

void GameUI::Render(SDL_Renderer* rend) {

	std::string scoreText = "Score: " + std::to_string(score);
	std::string livesText = "Lives: " + std::to_string(lives);
	std::string highScoreText = "High Score: " + std::to_string(highScore);


	SDL_Surface* scoreSurface = TTF_RenderText_Solid(Font, scoreText.c_str(), { 255, 255, 255 });
	SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(rend, scoreSurface);
	SDL_Rect scoreRect = { 10, 10, scoreSurface->w, scoreSurface->h };
	SDL_RenderCopy(rend, scoreTexture, NULL, &scoreRect);

	SDL_FreeSurface(scoreSurface);
	SDL_DestroyTexture(scoreTexture);


}