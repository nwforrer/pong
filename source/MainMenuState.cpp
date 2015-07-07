#include "Game.h"
#include "MainMenuState.h"
#include "MainState.h"

MainMenuState MainMenuState::mMainMenu;

bool MainMenuState::init(Game* game)
{
	mFont = TTF_OpenFont("OpenSans/OpenSans-Bold.ttf", 28);
	if (mFont == NULL)
	{
		printf("Failed to load OpenSans-Bold font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		SDL_Color textColor = { 255, 255, 255, 255 };
		if (!mResumeGameTextTexture.loadFromRenderedText(game->mRenderer, mFont, "[R]esume Game", textColor))
		{
			printf("Unable to render resume game texture!\n");
		}
		if (!mNewGameTextTexture.loadFromRenderedText(game->mRenderer, mFont, "[N]ew Game", textColor))
		{
			printf("Unable to render new game texture!\n");
		}

		if (!mQuitTextTexture.loadFromRenderedText(game->mRenderer, mFont, "[Q]uit", textColor))
		{
			printf("Unable to render quit game texture!\n");
		}
	}

	return true;
}

void MainMenuState::close()
{
	TTF_CloseFont(mFont);
	mFont = NULL;

	mResumeGameTextTexture.free();
	mNewGameTextTexture.free();
	mQuitTextTexture.free();
}

void MainMenuState::pause()
{

}

void MainMenuState::resume()
{

}

void MainMenuState::handleEvents(Game* game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				game->quit();
			} break;

			case SDL_KEYDOWN:
			{
				if (event.key.repeat == 0)
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_n:
						{
							game->changeState(MainState::instance());
						} break;

						case SDLK_q:
						{
							game->quit();
						} break;
					}
				}
			} break;
		}
	}
}

void MainMenuState::update(Game* game)
{
	// update
}

void MainMenuState::render(Game* game)
{
	SDL_SetRenderDrawColor(game->mRenderer, 0, 0, 0, 0);
	SDL_RenderClear(game->mRenderer);
	
	mNewGameTextTexture.render((SCREEN_WIDTH - mNewGameTextTexture.getWidth()) / 2, SCREEN_HEIGHT/2 - mNewGameTextTexture.getHeight()/2);
	mQuitTextTexture.render((SCREEN_WIDTH - mQuitTextTexture.getWidth()) / 2, SCREEN_HEIGHT/2 + mQuitTextTexture.getHeight()/2);

	SDL_RenderPresent(game->mRenderer);
}