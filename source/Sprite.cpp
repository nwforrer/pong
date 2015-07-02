#include "Sprite.h"

Sprite::Sprite()
{
	mTexture = NULL;
	mPosX = 0;
	mPosY = 0;
}

Sprite::~Sprite()
{
	free();
}

bool Sprite::init(SDLTexture* texture, int posX, int posY)
{
	mTexture = texture;
	mPosX = posX;
	mPosY = posY;

	return true;
}

void Sprite::free()
{
	mPosX = 0;
	mPosY = 0;
}

void Sprite::render()
{
	mTexture->render(mPosX, mPosY);
}