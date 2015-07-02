#include "SDLTimer.h"

SDLTimer::SDLTimer()
{
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}

void SDLTimer::start()
{
	mStarted = true;
	mPaused = false;

	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void SDLTimer::stop()
{
	mStarted = false;
	mPaused = false;

	mStartTicks = 0;
	mPausedTicks = 0;
}

void SDLTimer::pause()
{
	if (mStarted && !mPaused)
	{
		mPaused = true;

		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void SDLTimer::unpause()
{
	if (mStarted && mPaused)
	{
		mPaused = false;

		mStartTicks = SDL_GetTicks() - mPausedTicks;
		mPausedTicks = 0;
	}
}

Uint32 SDLTimer::getTicks()
{
	Uint32 time = 0;

	if (mStarted)
	{
		if (mPaused)
		{
			time = mPausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

bool SDLTimer::isStarted()
{
	return mStarted;
}

bool SDLTimer::isPaused()
{
	return mPaused;
}