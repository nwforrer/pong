#ifndef MAIN_MENU_STATE_H_
#define MAIN_MENU_STATE_H_

#include <SDL.h>
#include <SDL_ttf.h>

#include "GameState.h"
#include "SDLTexture.h"

class MainMenuState : public GameState
{
public:
	bool init(Game* game);
	void close();

	void pause();
	void resume();

	void handleEvents(Game* game);
	void update(Game* game);
	void render(Game* game);

	static MainMenuState* instance()
	{
		return &mMainMenu;
	}

protected:
	MainMenuState() { }

private:
	static MainMenuState mMainMenu;

	TTF_Font* mFont;

	SDLTexture mResumeGameTextTexture;
	SDLTexture mNewGameTextTexture;
	SDLTexture mQuitTextTexture;
};

#endif