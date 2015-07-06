#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include "Game.h"

class GameState
{
public:
	virtual bool init(Game* game) = 0;
	virtual void close() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvents(Game* game) = 0;
	virtual void update(Game* game) = 0;
	virtual void render(Game* game) = 0;

	void changeState(Game* game, GameState* state)
	{
		game->changeState(state);
	}

protected:
	GameState() { }
};

#endif