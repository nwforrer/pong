#ifndef PAUSE_MENU_STATE_H_
#define PAUSE_MENU_STATE_H_

#include "GameState.h"
#include "SDLTexture.h"

class PauseMenuState : public GameState
{
public:
	bool init(Game* game);
	void close();

	void pause();
	void resume();

	void handleEvents(Game* game);
	void update(Game* game);
	void render(Game* game);

	static PauseMenuState* instance()
	{
		return &mPauseMenu;
	}

protected:
	PauseMenuState() { }

private:
	static PauseMenuState mPauseMenu;
	
	TTF_Font* mFont;

	SDLTexture mResumeGameTextTexture;
	SDLTexture mNewGameTextTexture;
	SDLTexture mQuitTextTexture;
};

#endif