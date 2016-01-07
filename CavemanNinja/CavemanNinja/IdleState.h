#ifndef __IDLESTATE_H__
#define __IDLESTATE_H__

#include "PlayerState.h"

class Timer;

class IdleState : public PlayerState
{
public:
	IdleState();
	~IdleState();

	PlayerState* update(ModulePlayer& player);
	void enter(ModulePlayer& player);
	void OnCollision(Collider* c1, Collider* c2){};

private:
	Timer* timer;
};

#endif //__IDLESTATE_H__