#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "Sprite.h"

class Physics
{
public:
	static Physics& getInstance()
	{
		static Physics instance;
		return instance;
	}

	bool checkSpriteCollision(Sprite sprite1, Sprite sprite2);

private:
	Physics() {};

	Physics(Physics const&)				= delete;
	void operator=(Physics const&)		= delete;
};

#endif