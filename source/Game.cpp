#include "Game.h"

Game::Game()
{
	mWindow = NULL;
	mRenderer = NULL;
	mMainMenuScene = NULL;
}

Game::~Game()
{
	close();
}

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

				mMainMenuScene = new MainMenuScene(&mScenes, mRenderer);
			}
		}
	}

	return success;
}

void Game::close()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	mRenderer = NULL;

	if (mMainMenuScene != NULL)
	{
		mMainMenuScene->close();
		delete mMainMenuScene;
		mMainMenuScene = NULL;
	}

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::gameLoop()
{
	bool quit = false;
	SDL_Event e;

	SDLTimer timer;

	mScenes.push(mMainMenuScene);

	while (!quit)
	{
		Scene* currentScene = mScenes.top();

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			currentScene->handleInput(e);
			if (mScenes.size() == 0)
			{
				quit = true;
				break;
			}
			currentScene = mScenes.top();
		}

		//float timeStep = timer.getTicks() / 1000.0f;

		SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
		SDL_RenderClear(mRenderer);
		
		currentScene->handleRender();

		SDL_RenderPresent(mRenderer);

		timer.start();
	}
}