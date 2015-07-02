#ifndef SPRITE_H_
#define SPRITE_H_

#include "SDLTexture.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	bool init(SDLTexture* texture, int posX, int posY);
	void free();

	void render();

private:
	SDLTexture* mTexture;

	int mPosX;
	int mPosY;
};

#endif