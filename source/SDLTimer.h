#ifndef SDLTIMER_H_
#define SDLTIMER_H_

#include <SDL.h>

class SDLTimer
{
public:
	SDLTimer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();

	bool isStarted();
	bool isPaused();

private:
	Uint32 mStartTicks;

	Uint32 mPausedTicks;

	bool mPaused;
	bool mStarted;
};

#endif