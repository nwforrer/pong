#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <string>
#include <sstream>

#include "SDLTexture.h"
#include "SDLTimer.h"
#include "Sprite.h"
#include "Physics.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int PADDLE_VELOCITY = 4;

class Game
{
public:
	Game();
	~Game();

	bool init();
	void close();

	bool loadMedia();
	bool loadObjects();

	void gameLoop();

private:

	void handleKeyboardEvent(SDL_Event& e);

	void checkPaddleScreenCollision(Sprite* sprite);

	void checkBallCollisions();

	void updateScores();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	TTF_Font* mFont;

	int mPlayer1Score;
	int mPlayer2Score;

	SDLTexture mPlayer1ScoreTextTexture;
	SDLTexture mPlayer2ScoreTextTexture;

	SDLTexture mPlayer1Texture;
	SDLTexture mPlayer2Texture;
	SDLTexture mBallTexture;

	Sprite mPlayer1Sprite;
	Sprite mPlayer2Sprite;
	Sprite mBallSprite;

	Physics mPhysicsEngine;
};

#endif