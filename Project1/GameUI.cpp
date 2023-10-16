#include "GameUI.h"

GameUI::GameUI(const std::string& fontPath) {

	Font = TTF_OpenFont(fontPath.c_str(), 24);
	if (!Font) {
		SDL_Log("Failed to load font: %s", TTF_GetError());
	}
	score = 0;
	highScore = 0;
	lives = 3;



}

GameUI::~GameUI() {
	TTF_CloseFont(Font);
}

void GameUI::setScore(int newScore) {
	score = newScore;
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
	
	SDL_Surface* livesSurface = TTF_RenderText_Solid(Font, livesText.c_str(), { 255, 255, 255 });
	SDL_Texture* livesTexture = SDL_CreateTextureFromSurface(rend, livesSurface);
	SDL_Rect livesRect = { 10, 30, livesSurface->w, livesSurface->h };
	SDL_RenderCopy(rend, livesTexture, NULL, &livesRect);

	SDL_Surface* highScoreSurface = TTF_RenderText_Solid(Font, highScoreText.c_str(), { 255, 255, 255 });
	SDL_Texture* highScoreTexture = SDL_CreateTextureFromSurface(rend, highScoreSurface);
	SDL_Rect highScoreRect = { 10, 50, highScoreSurface->w, highScoreSurface->h };
	SDL_RenderCopy(rend, highScoreTexture, NULL, &highScoreRect);

	SDL_FreeSurface(scoreSurface);
	SDL_DestroyTexture(scoreTexture);


	SDL_FreeSurface(livesSurface);
	SDL_DestroyTexture(livesTexture);

	SDL_FreeSurface(highScoreSurface);
	SDL_DestroyTexture(highScoreTexture);
}
