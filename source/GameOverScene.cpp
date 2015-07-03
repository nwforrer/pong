#include "GameOverScene.h"

GameOverScene::GameOverScene(std::stack<Scene*> *scenes, SDL_Renderer *renderer) : Scene(scenes, renderer)
{
	init();
}

GameOverScene::~GameOverScene()
{
	close();
}

bool GameOverScene::init()
{
	mFont = TTF_OpenFont("OpenSans/OpenSans-Bold.ttf", 28);
	if (mFont == NULL)
	{
		printf("Failed to load OpenSans-Bold font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		SDL_Color textColor = { 255, 255, 255, 255 };
		if (!mGameOverTextTexture.loadFromRenderedText(mRenderer, mFont, "Game Over!", textColor))
		{
			printf("Unable to render resume game texture!\n");
		}
		if (!mMainMenuTextTexture.loadFromRenderedText(mRenderer, mFont, "Return to [m]enu", textColor))
		{
			printf("Unable to render new game texture!\n");
		}
	}

	return true;
}

void GameOverScene::close()
{
	TTF_CloseFont(mFont);
	mFont = NULL;

	mGameOverTextTexture.free();
	mMainMenuTextTexture.free();
}

void GameOverScene::handleRender()
{
	mGameOverTextTexture.render((SCREEN_WIDTH - mGameOverTextTexture.getWidth()) / 2, SCREEN_HEIGHT/2 - mGameOverTextTexture.getHeight()/2);
	mMainMenuTextTexture.render((SCREEN_WIDTH - mMainMenuTextTexture.getWidth()) / 2, SCREEN_HEIGHT/2 + mMainMenuTextTexture.getHeight()/2);
}

void GameOverScene::handleInput(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_m:
			{
				mScenes->pop();
			} break;
		}
	}
}