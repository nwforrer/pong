#include "SDLTexture.h"

SDLTexture::SDLTexture()
{
	mTexture = NULL;
	mRenderer = NULL;
	mWidth = 0;
	mHeight = 0;
}

SDLTexture::~SDLTexture()
{
	free();
}

void SDLTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}

	// SDLTexture is not responsible for freeing the renderer
	mRenderer = NULL;
}

bool SDLTexture::loadFromFile(SDL_Renderer* renderer, std::string path)
{
	free();

	mRenderer = renderer;

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

void SDLTexture::render(int x, int y)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy(mRenderer, mTexture, NULL, &renderQuad);
}

int SDLTexture::getWidth()
{
	return mWidth;
}

int SDLTexture::getHeight()
{
	return mHeight;
}