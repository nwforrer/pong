#include "Game.h"

Game::Game()
{
	mWindow = NULL;
	mRenderer = NULL;

	mFont = NULL;

	mPlayer1Score = 0;
	mPlayer2Score = 0;
}

Game::~Game()
{
	close();
}

bool Game::init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		mWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (mWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (mRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				}

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void Game::close()
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

	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	mRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::gameLoop()
{
	bool quit = false;
	SDL_Event e;

	SDLTimer timer;

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					{
						quit = true;
					} break;
				}
			}

			handleKeyboardEvent(e);
		}

		//float timeStep = timer.getTicks() / 1000.0f;

		mPlayer1Sprite.update();
		mPlayer2Sprite.update();
		mBallSprite.update();

		checkPaddleScreenCollision(&mPlayer1Sprite);
		checkPaddleScreenCollision(&mPlayer2Sprite);

		checkBallCollisions();

		SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
		SDL_RenderClear(mRenderer);

		mPlayer1Sprite.render();
		mPlayer2Sprite.render();
		mBallSprite.render();

		mPlayer1ScoreTextTexture.render(10, 10);
		mPlayer2ScoreTextTexture.render(SCREEN_WIDTH - mPlayer2ScoreTextTexture.getWidth() - 10, 10);
		
		SDL_RenderPresent(mRenderer);

		timer.start();
	}
}

bool Game::loadMedia()
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

	return success;
}

bool Game::loadObjects()
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
		mBallSprite.setVelX(-2);
		mBallSprite.setVelY(1);
	}

	return success;
}

void Game::handleKeyboardEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
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

void Game::checkPaddleScreenCollision(Sprite* sprite)
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

void Game::checkBallCollisions()
{
	if (mPhysicsEngine.checkSpriteCollision(mBallSprite, mPlayer1Sprite))
	{
		mBallSprite.setVelX(mBallSprite.getVelX() * -1);
	}
	else if (mPhysicsEngine.checkSpriteCollision(mBallSprite, mPlayer2Sprite))
	{
		mBallSprite.setVelX(mBallSprite.getVelX() * -1);
	}

	if (mBallSprite.getPosY() < 0 || mBallSprite.getPosY() + mBallSprite.getHeight() > SCREEN_HEIGHT)
	{
		mBallSprite.setVelY(mBallSprite.getVelY() * -1);
	}

	if (mBallSprite.getPosX() < 0)
	{
		mBallSprite.setVelX(mBallSprite.getVelX() * -1);

		++mPlayer2Score;
		updateScores();
	}
	else if (mBallSprite.getPosX() + mBallSprite.getWidth() > SCREEN_WIDTH)
	{
		mBallSprite.setVelX(mBallSprite.getVelX() * -1);

		++mPlayer1Score;
		updateScores();
	}
}

void Game::updateScores()
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
}