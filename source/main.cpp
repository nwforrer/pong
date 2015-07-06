#include <stdio.h>

#include "Game.h"
#include "MainMenuState.h"

int main(int argc, char **argv)
{
	Game game;

	if (!game.init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		game.changeState(MainMenuState::instance());

		while (game.isRunning())
		{
			game.handleEvents();
			game.update();
			game.render();
		}
	}

	game.close();

	return 0;
}
