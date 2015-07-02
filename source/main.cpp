#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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

TTF_Font* gFont = NULL;

SDLTexture gTextTexture;

SDLTexture gPlayer1Texture;
SDLTexture gPlayer2Texture;
SDLTexture gBallTexture;

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

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	if (!gPlayer1Texture.loadFromFile(gRenderer, "player1-paddle.png"))
	{
		printf("Failed to load player1 paddle image!\n");
		success = false;
	}

	if (!gPlayer2Texture.loadFromFile(gRenderer, "player2-paddle.png"))
	{
		printf("Failed to load player2 paddle image!\n");
		success = false;
	}

	if (!gBallTexture.loadFromFile(gRenderer, "ball.png"))
	{
		printf("Failed to load ball image!\n");
		success = false;
	}

	gFont = TTF_OpenFont("OpenSans/OpenSans-Bold.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load OpenSans-Bold font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		SDL_Color textColor = { 255, 255, 255 };
		if (!gTextTexture.loadFromRenderedText(gRenderer, gFont, "This is some text.", textColor))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	return success;
}

void close()
{
	gPlayer1Texture.free();
	gPlayer2Texture.free();
	gBallTexture.free();

	gTextTexture.free();

	TTF_CloseFont(gFont);
	gFont = NULL;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	TTF_Quit();
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

				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
				SDL_RenderClear(gRenderer);

				gPlayer1Texture.render(50, (SCREEN_HEIGHT - gPlayer1Texture.getHeight()) / 2);
				gPlayer2Texture.render(SCREEN_WIDTH - gPlayer2Texture.getWidth() - 50, (SCREEN_HEIGHT - gPlayer2Texture.getHeight()) / 2);
				gBallTexture.render((SCREEN_WIDTH - gBallTexture.getWidth()) / 2, 100);

				gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTextTexture.getHeight()) / 2);
				
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	close();

	return 0;
}
