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
		if (!game.loadMedia() || !game.loadObjects())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			game.gameLoop();
		}
	}

	game.close();

	return 0;
}
