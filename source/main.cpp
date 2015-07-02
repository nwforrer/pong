#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

#include "SDLTexture.h"
#include "SDLTimer.h"
#include "Sprite.h"
#include "Physics.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int PADDLE_VELOCITY = 4;

bool init();
bool loadMedia();
bool loadObjects();
void close();

void handleKeyboardEvent(SDL_Event& e);

void checkPaddleScreenCollision(Sprite sprite);

void checkBallCollisions();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

TTF_Font* gFont = NULL;

SDLTexture gTextTexture;

SDLTexture gPlayer1Texture;
SDLTexture gPlayer2Texture;
SDLTexture gBallTexture;

Sprite gPlayer1Sprite;
Sprite gPlayer2Sprite;
Sprite gBallSprite;

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
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
		SDL_Color textColor = { 255, 255, 255, 255 };
		if (!gTextTexture.loadFromRenderedText(gRenderer, gFont, "This is some text.", textColor))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	return success;
}

bool loadObjects()
{
	bool success = true;

	if (!gPlayer1Sprite.init(&gPlayer1Texture, 50, (SCREEN_HEIGHT - gPlayer1Texture.getHeight()) / 2))
	{
		printf("Could not initialize player1 sprite!\n");
		success = false;
	}

	if (!gPlayer2Sprite.init(&gPlayer2Texture, SCREEN_WIDTH - gPlayer2Texture.getWidth() - 50, (SCREEN_HEIGHT - gPlayer2Texture.getHeight()) / 2))
	{
		printf("Could not initialize player2 sprite!\n");
		success = false;
	}

	if (!gBallSprite.init(&gBallTexture, (SCREEN_WIDTH - gBallTexture.getWidth()) / 2, 100))
	{
		printf("Could not initialize ball sprite!\n");
		success = false;
	}
	else
	{
		gBallSprite.setVelX(-2);
		gBallSprite.setVelY(1);
	}

	return success;
}

void close()
{
	gPlayer1Texture.free();
	gPlayer2Texture.free();
	gBallTexture.free();

	gTextTexture.free();

	gPlayer1Sprite.free();
	gPlayer2Sprite.free();
	gBallSprite.free();

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

void handleKeyboardEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_w:
			{
				gPlayer1Sprite.addVelY(-PADDLE_VELOCITY);
			} break;
			
			case SDLK_s:
			{
				gPlayer1Sprite.addVelY(PADDLE_VELOCITY);
			} break;

			case SDLK_UP:
			{
				gPlayer2Sprite.addVelY(-PADDLE_VELOCITY);
			} break;

			case SDLK_DOWN:
			{
				gPlayer2Sprite.addVelY(PADDLE_VELOCITY);
			}
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_w:
			{
				gPlayer1Sprite.addVelY(PADDLE_VELOCITY);
			} break;
			
			case SDLK_s:
			{
				gPlayer1Sprite.addVelY(-PADDLE_VELOCITY);
			} break;

			case SDLK_UP:
			{
				gPlayer2Sprite.addVelY(PADDLE_VELOCITY);
			} break;

			case SDLK_DOWN:
			{
				gPlayer2Sprite.addVelY(-PADDLE_VELOCITY);
			}
		}
	}
}

void checkPaddleScreenCollision(Sprite* sprite)
{
	if (sprite->getPosY() < 0)
	{
		sprite->setPosY(0);
	}
	else if (sprite->getPosY() + sprite->getHeight() > SCREEN_HEIGHT)
	{
		sprite->setPosY(SCREEN_HEIGHT - sprite->getHeight());
	}
}

void checkBallCollisions()
{
	if (Physics::getInstance().checkSpriteCollision(gBallSprite, gPlayer1Sprite))
	{
		gBallSprite.setVelX(gBallSprite.getVelX() * -1);
	}
	else if (Physics::getInstance().checkSpriteCollision(gBallSprite, gPlayer2Sprite))
	{
		gBallSprite.setVelX(gBallSprite.getVelX() * -1);
	}

	if (gBallSprite.getPosY() < 0 || gBallSprite.getPosY() + gBallSprite.getHeight() > SCREEN_HEIGHT)
	{
		gBallSprite.setVelY(gBallSprite.getVelY() * -1);
	}
}

int main(int argc, char **argv)
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia() || !loadObjects())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit = false;
			SDL_Event e;

			SDLTimer timer;

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

					handleKeyboardEvent(e);
				}

				//float timeStep = timer.getTicks() / 1000.0f;

				gPlayer1Sprite.update();
				gPlayer2Sprite.update();
				gBallSprite.update();

				checkPaddleScreenCollision(&gPlayer1Sprite);
				checkPaddleScreenCollision(&gPlayer2Sprite);

				checkBallCollisions();

				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
				SDL_RenderClear(gRenderer);

				gPlayer1Sprite.render();
				gPlayer2Sprite.render();
				gBallSprite.render();

				gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTextTexture.getHeight()) / 2);
				
				SDL_RenderPresent(gRenderer);

				timer.start();
			}
		}
	}

	close();

	return 0;
}
