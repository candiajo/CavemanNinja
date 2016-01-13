#include "Timer.h"

Timer::Timer() : life_time(0), start_time(0)
{}

Timer::Timer(int life_time) : life_time(life_time)
{}

Timer::~Timer()
{}

void Timer::StartTimer(int time)
{
	if (time > 0) life_time = time;		// restarts the timer with a new time
	start_time = SDL_GetTicks();
}

bool Timer::TimeOver() const
{
	int elapsed_time = (SDL_GetTicks() - start_time);

	if (elapsed_time > life_time)
		return true;
	else
		return false;
}

int Timer::ElapsedTime() const
{
	return (SDL_GetTicks() - start_time);
}