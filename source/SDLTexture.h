#ifndef SDLTEXTURE_H_
#define SDLTEXTURE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class SDLTexture
{
public:
	SDLTexture();
	~SDLTexture();

	bool loadFromFile(SDL_Renderer* renderer, std::string path);

	void free();

	void render(int x, int y);

	int getWidth();
	int getHeight();

private:
	SDL_Texture* mTexture;
	SDL_Renderer* mRenderer;

	int mWidth;
	int mHeight;
};

#endif
