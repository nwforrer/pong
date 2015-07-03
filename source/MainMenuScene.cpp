#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(std::stack<Scene*> *scenes, SDL_Renderer *renderer) : Scene(scenes, renderer)
{
	init();
}

MainMenuScene::~MainMenuScene()
{
	close();
}

bool MainMenuScene::init()
{
	mFont = TTF_OpenFont("OpenSans/OpenSans-Bold.ttf", 28);
	if (mFont == NULL)
	{
		printf("Failed to load OpenSans-Bold font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		SDL_Color textColor = { 255, 255, 255, 255 };
		if (!mResumeGameTextTexture.loadFromRenderedText(mRenderer, mFont, "[R]esume Game", textColor))
		{
			printf("Unable to render resume game texture!\n");
		}
		if (!mNewGameTextTexture.loadFromRenderedText(mRenderer, mFont, "[N]ew Game", textColor))
		{
			printf("Unable to render new game texture!\n");
		}

		if (!mQuitTextTexture.loadFromRenderedText(mRenderer, mFont, "[Q]uit", textColor))
		{
			printf("Unable to render quit game texture!\n");
		}
	}

	mMainScene = new MainScene(mScenes, mRenderer);

	mGameInProgress = false;

	return true;
}

void MainMenuScene::close()
{
	TTF_CloseFont(mFont);
	mFont = NULL;

	mResumeGameTextTexture.free();
	mNewGameTextTexture.free();
	mQuitTextTexture.free();

	if (mMainScene != NULL)
	{
		mMainScene->close();
		delete mMainScene;
		mMainScene = NULL;
	}
}

void MainMenuScene::handleRender()
{
	if (mGameInProgress)
	{
		mResumeGameTextTexture.render((SCREEN_WIDTH - mResumeGameTextTexture.getWidth()) / 2, 20);
	}
	mNewGameTextTexture.render((SCREEN_WIDTH - mNewGameTextTexture.getWidth()) / 2, SCREEN_HEIGHT/2 - mNewGameTextTexture.getHeight()/2);
	mQuitTextTexture.render((SCREEN_WIDTH - mQuitTextTexture.getWidth()) / 2, SCREEN_HEIGHT/2 + mQuitTextTexture.getHeight()/2);
}

void MainMenuScene::handleInput(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_n:
			{
				mGameInProgress = true;

				mMainScene->close();
				mMainScene->init();
				mScenes->push(mMainScene);
			} break;

			case SDLK_r:
			{
				if (mGameInProgress)
				{
					mScenes->push(mMainScene);
				}
			} break;

			case SDLK_q:
			{
				mScenes->pop();
			}
		}
	}
}
