#include "Physics.h"

bool Physics::checkSpriteCollision(Sprite a, Sprite b)
{
	bool collision = true;

	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.getPosX();
	rightA = a.getPosX() + a.getWidth();
	topA = a.getPosY();
	bottomA = a.getPosY() + a.getHeight();

	leftB = b.getPosX();
	rightB = b.getPosX() + b.getWidth();
	topB = b.getPosY();
	bottomB = b.getPosY() + b.getHeight();

	if (bottomA <= topB)
	{
		collision = false;
	}
	else if (topA >= bottomB)
	{
		collision = false;
	}
	else if (rightA <= leftB)
	{
		collision = false;
	}
	else if (leftA >= rightB)
	{
		collision = false;
	}

	return collision;
}