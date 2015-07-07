#ifndef GAME_OVER_STATE_H_
#define GAME_OVER_STATE_H_

#include <SDL.h>
#include <SDL_ttf.h>

#include "GameState.h"
#include "SDLTexture.h"

class GameOverState : public GameState
{
public:
	bool init(Game* game);
	void close();

	void pause();
	void resume();

	void handleEvents(Game* game);
	void update(Game* game);
	void render(Game* game);

	static GameOverState* instance()
	{
		return &mGameOverState;
	}

protected:
	GameOverState() { }

private:
	static GameOverState mGameOverState;

	TTF_Font* mFont;

	SDLTexture mGameOverTextTexture;
	SDLTexture mMainMenuTextTexture;
};

#endif