#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <stdio.h>
#include <stack>

#include "Scene.h"
#include "MainMenuScene.h"
#include "SDLTimer.h"

class Game
{
public:
	Game();
	~Game();

	bool init();
	void close();

	void gameLoop();

private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	MainMenuScene *mMainMenuScene;
	std::stack<Scene*> mScenes;
};

#endif