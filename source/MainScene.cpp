#include "MainScene.h"

MainScene::MainScene(std::stack<Scene*> *scenes, SDL_Renderer *renderer) : Scene(scenes, renderer)
{
	init();
}

MainScene::~MainScene()
{
	close();
}

bool MainScene::init()
{
	mFont = NULL;

	mPaddleHitSound = NULL;
	mWallHitSound = NULL;

	mPlayer1Score = 0;
	mPlayer2Score = 0;

	mLockBallCollisionCheck = false;

	loadMedia();
	loadObjects();

	return true;
}

void MainScene::close()
{
	mPlayer1Texture.free();
	mPlayer2Texture.free();
	mBallTexture.free();

	mPlayer1ScoreTextTexture.free();
	mPlayer2ScoreTextTexture.free();

	mPlayer1Sprite.free();
	mPlayer2Sprite.free();
	mBallSprite.free();

	TTF_CloseFont(mFont);
	mFont = NULL;

	Mix_FreeChunk(mPaddleHitSound);
	Mix_FreeChunk(mWallHitSound);
	mPaddleHitSound = NULL;
	mWallHitSound = NULL;
}

void MainScene::handleRender()
{
	mPlayer1Sprite.update();
	mPlayer2Sprite.update();
	mBallSprite.update();

	checkPaddleScreenCollision(&mPlayer1Sprite);
	checkPaddleScreenCollision(&mPlayer2Sprite);

	checkBallCollisions();

	mPlayer1Sprite.render();
	mPlayer2Sprite.render();
	mBallSprite.render();

	mPlayer1ScoreTextTexture.render(10, 10);
	mPlayer2ScoreTextTexture.render(SCREEN_WIDTH - mPlayer2ScoreTextTexture.getWidth() - 10, 10);
}

void MainScene::handleInput(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_ESCAPE:
			{
				mScenes->pop();
			} break;
			case SDLK_w:
			{
				mPlayer1Sprite.addVelY(-PADDLE_VELOCITY);
			} break;
			
			case SDLK_s:
			{
				mPlayer1Sprite.addVelY(PADDLE_VELOCITY);
			} break;

			case SDLK_UP:
			{
				mPlayer2Sprite.addVelY(-PADDLE_VELOCITY);
			} break;

			case SDLK_DOWN:
			{
				mPlayer2Sprite.addVelY(PADDLE_VELOCITY);
			}
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_w:
			{
				mPlayer1Sprite.addVelY(PADDLE_VELOCITY);
			} break;
			
			case SDLK_s:
			{
				mPlayer1Sprite.addVelY(-PADDLE_VELOCITY);
			} break;

			case SDLK_UP:
			{
				mPlayer2Sprite.addVelY(PADDLE_VELOCITY);
			} break;

			case SDLK_DOWN:
			{
				mPlayer2Sprite.addVelY(-PADDLE_VELOCITY);
			}
		}
	}
}

bool MainScene::loadMedia()
{
	bool success = true;

	if (!mPlayer1Texture.loadFromFile(mRenderer, "player1-paddle.png"))
	{
		printf("Failed to load player1 paddle image!\n");
		success = false;
	}

	if (!mPlayer2Texture.loadFromFile(mRenderer, "player2-paddle.png"))
	{
		printf("Failed to load player2 paddle image!\n");
		success = false;
	}

	if (!mBallTexture.loadFromFile(mRenderer, "ball.png"))
	{
		printf("Failed to load ball image!\n");
		success = false;
	}

	mFont = TTF_OpenFont("OpenSans/OpenSans-Bold.ttf", 28);
	if (mFont == NULL)
	{
		printf("Failed to load OpenSans-Bold font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		updateScores();
	}

	mPaddleHitSound = Mix_LoadWAV("paddle-hit.wav");
	if (mPaddleHitSound == NULL)
	{
		printf("Failed to load paddle hit sound! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	mWallHitSound = Mix_LoadWAV("wall-hit.wav");
	if (mWallHitSound == NULL)
	{
		printf("Failed to load wall hit sound! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

bool MainScene::loadObjects()
{
	bool success = true;

	if (!mPlayer1Sprite.init(&mPlayer1Texture, 50, (SCREEN_HEIGHT - mPlayer1Texture.getHeight()) / 2))
	{
		printf("Could not initialize player1 sprite!\n");
		success = false;
	}

	if (!mPlayer2Sprite.init(&mPlayer2Texture, SCREEN_WIDTH - mPlayer2Texture.getWidth() - 50, (SCREEN_HEIGHT - mPlayer2Texture.getHeight()) / 2))
	{
		printf("Could not initialize player2 sprite!\n");
		success = false;
	}

	if (!mBallSprite.init(&mBallTexture, (SCREEN_WIDTH - mBallTexture.getWidth()) / 2, 100))
	{
		printf("Could not initialize ball sprite!\n");
		success = false;
	}
	else
	{
		resetBall();
	}

	return success;
}

void MainScene::resetBall()
{
	mBallSprite.setPosX((SCREEN_WIDTH - mBallSprite.getWidth()) / 2);
	mBallSprite.setPosY(((SCREEN_HEIGHT - mBallSprite.getHeight()) / 2) - 100);

	mBallSprite.setVelX(-4);
	mBallSprite.setVelY(3);
}

void MainScene::checkPaddleScreenCollision(Sprite* sprite)
{
	if (sprite->getPosY() < 0)
	{
		sprite->setPosY(0);
	}
	else if (sprite->getPosY() + sprite->getHeight() > SCREEN_HEIGHT)
	{
		sprite->setPosY(SCREEN_HEIGHT - sprite->getHeight());
	}
}

void MainScene::checkBallCollisions()
{
	if (!mLockBallCollisionCheck)
	{
		if (mPhysicsEngine.checkSpriteCollision(mBallSprite, mPlayer1Sprite))
		{
			mBallSprite.setVelX(mBallSprite.getVelX() * -1);

			int paddleCenter = mPlayer1Sprite.getPosY() + (mPlayer1Sprite.getHeight() / 2);
			int ballCenter = mBallSprite.getPosY() + (mBallSprite.getHeight() / 2);

			if (ballCenter >= paddleCenter)
			{
				mBallSprite.setVelY(std::abs(mBallSprite.getVelY()));
			}
			else
			{
				mBallSprite.setVelY(-std::abs(mBallSprite.getVelY()));
			}

			mLockBallCollisionCheck = true;
			
			if (Mix_PlayChannel(-1, mPaddleHitSound, 0) == -1)
			{
				printf("Mix_PlayChannel Error: %s\n", Mix_GetError());
			}
		}
		else if (mPhysicsEngine.checkSpriteCollision(mBallSprite, mPlayer2Sprite))
		{
			mBallSprite.setVelX(mBallSprite.getVelX() * -1);

			int paddleCenter = mPlayer2Sprite.getPosY() + (mPlayer2Sprite.getHeight() / 2);
			int ballCenter = mBallSprite.getPosY() + (mBallSprite.getHeight() / 2);

			if (ballCenter >= paddleCenter)
			{
				mBallSprite.setVelY(std::abs(mBallSprite.getVelY()));
			}
			else
			{
				mBallSprite.setVelY(-std::abs(mBallSprite.getVelY()));
			}

			mLockBallCollisionCheck = true;

			if (Mix_PlayChannel(-1, mPaddleHitSound, 0) == -1)
			{
				printf("Mix_PlayChannel Error: %s\n", Mix_GetError());
			}
		}
	}
	else if ((mBallSprite.getVelX() > 0 && mBallSprite.getPosX() > SCREEN_WIDTH / 2) ||
			(mBallSprite.getVelX() < 0 && mBallSprite.getPosX() < SCREEN_WIDTH / 2))
	{
		mLockBallCollisionCheck = false;
	}

	if (mBallSprite.getPosY() < 0 || mBallSprite.getPosY() + mBallSprite.getHeight() > SCREEN_HEIGHT)
	{
		mBallSprite.setVelY(mBallSprite.getVelY() * -1);
		Mix_PlayChannel(-1, mWallHitSound, 0);
	}

	if (mBallSprite.getPosX() < 0)
	{
		resetBall();

		++mPlayer2Score;
		updateScores();
	}
	else if (mBallSprite.getPosX() + mBallSprite.getWidth() > SCREEN_WIDTH)
	{
		resetBall();

		++mPlayer1Score;
		updateScores();
	}
}

void MainScene::updateScores()
{
	std::stringstream player1Text;
	std::stringstream player2Text;

	SDL_Color textColor = { 255, 255, 255, 255 };

	player1Text << "Score: " << mPlayer1Score;
	player2Text << "Score: " << mPlayer2Score;

	if (!mPlayer1ScoreTextTexture.loadFromRenderedText(mRenderer, mFont, player1Text.str().c_str(), textColor))
	{
		printf("Unable to render player 1 score texture!\n");
	}
	if (!mPlayer2ScoreTextTexture.loadFromRenderedText(mRenderer, mFont, player2Text.str().c_str(), textColor))
	{
		printf("Unable to render player 2 score texture!\n");
	}

	if (mPlayer1Score >= 3 || mPlayer2Score >= 3)
	{
		mScenes->pop();
		mScenes->push(new GameOverScene(mScenes, mRenderer));
	}
}