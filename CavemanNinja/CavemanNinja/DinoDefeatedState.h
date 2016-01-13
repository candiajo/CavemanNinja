#ifndef __DINODEFEATEDSTATE_H__
#define __DINODEFEATEDSTATE_H__

#include "DinoState.h"

#define DINO_LEFT_LIMIT -30
#define DINO_DOWN_LIMIT 120

class Timer;

class DinoDefeatedState : public DinoState
{
public:
	DinoDefeatedState() {};
	~DinoDefeatedState();

	DinoState* Update(ModuleDino& dino);
	void Enter(ModuleDino& dino);

private:
	Timer* timer;
};

#endif //__DINODEFEATEDSTATE_H__