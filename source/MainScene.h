#ifndef MAIN_SCENE_H_
#define MAIN_SCENE_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <cmath>

#include "Scene.h"
#include "SDLTexture.h"
#include "SDLTimer.h"
#include "Sprite.h"
#include "Physics.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int PADDLE_VELOCITY = 3;

class MainScene : public Scene
{
public:
	MainScene(std::stack<Scene*> *scenes, SDL_Renderer *renderer);
	~MainScene();

	bool init();
	void close();

	void handleRender();
	void handleInput(SDL_Event& e);

private:
	bool loadMedia();
	bool loadObjects();

	void checkPaddleScreenCollision(Sprite* sprite);

	void checkBallCollisions();

	void updateScores();

	void resetBall();

	TTF_Font* mFont;

	Mix_Chunk* mPaddleHitSound;
	Mix_Chunk* mWallHitSound;

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

	// after a ball collides with a paddle, don't recheck collision until the
	// ball croses the center of the screen in order to avoid multiple collisions
	// on one paddle.
	bool mLockBallCollisionCheck;
};

#endif