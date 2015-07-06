#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <stdio.h>
#include <vector>

#include "SDLTimer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class GameState;

class Game
{
public:
	bool init();
	void close();

	void changeState(GameState* state);
	void pushState(GameState* state);
	void popState();

	void handleEvents();
	void update();
	void render();

	bool isRunning() { return mRunning; }
	void quit() { mRunning = false; }

	SDL_Renderer* mRenderer;

private:
	SDL_Window* mWindow;

	std::vector<GameState*> mStates;

	bool mRunning;
};

#endif