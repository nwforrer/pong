#ifndef MAIN_MENU_SCENE_H_
#define MAIN_MENU_SCENE_H_

#include <SDL.h>
#include <SDL_ttf.h>

#include "Scene.h"
#include "MainScene.h"
#include "SDLTexture.h"

class MainMenuScene : public Scene
{
public:
	MainMenuScene(std::stack<Scene*> *scenes, SDL_Renderer *renderer);
	~MainMenuScene();

	bool init();
	void close();

	void handleRender();
	void handleInput(SDL_Event& e);

private:
	TTF_Font* mFont;

	SDLTexture mResumeGameTextTexture;
	SDLTexture mNewGameTextTexture;
	SDLTexture mQuitTextTexture;

	MainScene *mMainScene;

	bool mGameInProgress;
};

#endif