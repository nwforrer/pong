#include <stdio.h>

#include "Game.h"

int main(int argc, char **argv)
{
	Game game;

	if (!game.init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		game.gameLoop();
	}

	game.close();

	return 0;
}
