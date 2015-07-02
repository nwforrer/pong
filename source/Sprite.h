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

	void update();
	void render();

	void addVelX(int velX);
	void addVelY(int velY);

	int getPosX();
	int getPosY();

	void setPosX(int posX);
	void setPosY(int posY);

	int getWidth();
	int getHeight();

private:
	SDLTexture* mTexture;

	int mPosX;
	int mPosY;

	int mVelX;
	int mVelY;
};

#endif