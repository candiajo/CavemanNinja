#ifndef __TIMER_H__
#define __TIMER_H__

#include "SDL.h"

class Timer
{
public:
	Timer();
	Timer(int life_time);
	~Timer();

	void StartTimer(int time = 0);
	bool TimeOver() const;
	int ElapsedTime() const;

private:
	int start_time;
	int life_time;	// in milliseconds
};

#endif //__TIMER_H__