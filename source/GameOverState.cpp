#include "GameOverState.h"
#include "MainMenuState.h"

GameOverState GameOverState::mGameOverState;

bool GameOverState::init(Game* game)
{
	mFont = TTF_OpenFont("OpenSans/OpenSans-Bold.ttf", 28);
	if (mFont == NULL)
	{
		printf("Failed to load OpenSans-Bold font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		SDL_Color textColor = { 255, 255, 255, 255 };
		if (!mGameOverTextTexture.loadFromRenderedText(game->mRenderer, mFont, "Game Over!", textColor))
		{
			printf("Unable to render resume game texture!\n");
		}
		if (!mMainMenuTextTexture.loadFromRenderedText(game->mRenderer, mFont, "Return to [m]enu", textColor))
		{
			printf("Unable to render new game texture!\n");
		}
	}

	return true;
}

void GameOverState::close()
{
	TTF_CloseFont(mFont);
	mFont = NULL;

	mGameOverTextTexture.free();
	mMainMenuTextTexture.free();
}

void GameOverState::pause()
{

}

void GameOverState::resume()
{
	
}

void GameOverState::handleEvents(Game* game)
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
						case SDLK_m:
						{
							game->changeState(MainMenuState::instance());
						} break;
					}
				}
			}
		}
	}
}

void GameOverState::update(Game* game)
{
	// update
}

void GameOverState::render(Game* game)
{
	SDL_SetRenderDrawColor(game->mRenderer, 0, 0, 0, 0);
	SDL_RenderClear(game->mRenderer);
	
	mGameOverTextTexture.render((SCREEN_WIDTH - mGameOverTextTexture.getWidth()) / 2, SCREEN_HEIGHT/2 - mGameOverTextTexture.getHeight()/2);
	mMainMenuTextTexture.render((SCREEN_WIDTH - mMainMenuTextTexture.getWidth()) / 2, SCREEN_HEIGHT/2 + mMainMenuTextTexture.getHeight()/2);

	SDL_RenderPresent(game->mRenderer);
}