#ifndef __SUPERHITSTATE_H__
#define __SUPERHITSTATE_H__

#include "DinoState.h"

class Timer;

class SuperHitState : public DinoState
{
public:
	SuperHitState() {};
	~SuperHitState();

	DinoState* update(ModuleDino& dino);
	void enter(ModuleDino& dino);

private:
	Timer* timer;
};

#endif //__SUPERHITSTATE_H__