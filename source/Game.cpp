#include "Game.h"
#include "GameState.h"

bool Game::init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	mRunning = true;

	return success;
}

void Game::close()
{
	while (!mStates.empty())
	{
		mStates.back()->close();
		mStates.pop_back();
	}
	
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	mRenderer = NULL;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::changeState(GameState* state)
{
	if (!mStates.empty())
	{
		mStates.back()->close();
		mStates.pop_back();
	}

	mStates.push_back(state);
	mStates.back()->init(this);
}

void Game::pushState(GameState* state)
{
	if (!mStates.empty()) 
	{
		mStates.back()->pause();
	}

	mStates.push_back(state);
	mStates.back()->init(this);
}

void Game::popState()
{
	if (!mStates.empty())
	{
		mStates.back()->close();
		mStates.pop_back();
	}

	if (!mStates.empty())
	{
		mStates.back()->resume();
	}
}

void Game::handleEvents()
{
	mStates.back()->handleEvents(this);
}

void Game::update()
{
	mStates.back()->update(this);
}

void Game::render()
{
	mStates.back()->render(this);
}
