#include "Sprite.h"

Sprite::Sprite()
{
	mTexture = NULL;

	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;
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

	mVelX = 0;
	mVelY = 0;
}

void Sprite::update()
{
	mPosY += mVelY;
	mPosX += mVelX;
}

void Sprite::render()
{
	mTexture->render((int)mPosX, (int)mPosY);
}

void Sprite::addVelX(int velX)
{
	mVelX += velX;
}

void Sprite::addVelY(int velY)
{
	mVelY += velY;
}

void Sprite::setVelX(int velX)
{
	mVelX = velX;
}

void Sprite::setVelY(int velY)
{
	mVelY = velY;
}

int Sprite::getVelX()
{
	return mVelX;
}

int Sprite::getVelY()
{
	return mVelY;
}

int Sprite::getPosX()
{
	return mPosX;
}

int Sprite::getPosY()
{
	return mPosY;
}

void Sprite::setPosX(int posX)
{
	mPosX = posX;
}

void Sprite::setPosY(int posY)
{
	mPosY = posY;
}

int Sprite::getWidth()
{
	return mTexture->getWidth();
}

int Sprite::getHeight()
{
	return mTexture->getHeight();
}