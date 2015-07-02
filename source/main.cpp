#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "SDLTexture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDLTexture gStickGuy;
SDLTexture gBackground;

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	if (!gStickGuy.loadFromFile(gRenderer, "stick-guy.png"))
	{
		printf("Failed to load stick guy image!\n");
		success = false;
	}

	if (!gBackground.loadFromFile(gRenderer, "background.png"))
	{
		printf("Failed to load background image!\n");
		success = false;
	}

	return success;
}

void close()
{
	gStickGuy.free();
	gBackground.free();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char **argv)
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit = false;
			SDL_Event e;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN)
					{
						switch(e.key.keysym.sym)
						{
							case SDLK_ESCAPE:
							{
								quit = true;
							} break;
						}
					}
				}

				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				gBackground.render(0, 0);
				gStickGuy.render(300, 50);
				
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	close();

	return 0;
}
