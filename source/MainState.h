#ifndef MAIN_STATE_H
#define MAIN_STATE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <cmath>

#include "GameState.h"
#include "SDLTexture.h"
#include "SDLTimer.h"
#include "Sprite.h"
#include "Physics.h"

const int PADDLE_VELOCITY = 3;
const int WIN_SCORE = 5;

class MainState : public GameState
{
public:
	bool init(Game* game);
	void close();

	void pause();
	void resume();

	void handleEvents(Game* game);
	void update(Game* game);
	void render(Game* game);

	static MainState* instance()
	{
		return &mMainState;
	}

protected:
	MainState() { }

private:
	static MainState mMainState;

	bool loadMedia(Game* game);
	bool loadObjects();

	void checkPaddleScreenCollision(Sprite* sprite);

	void checkBallCollisions(Game* game);

	void updateScores(Game* game);

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