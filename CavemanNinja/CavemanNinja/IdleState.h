#ifndef __IDLESTATE_H__
#define __IDLESTATE_H__

#include "PlayerState.h"

class Timer;

class IdleState : public PlayerState
{
public:
	IdleState() {};
	~IdleState();

	PlayerState* Update(ModulePlayer& player);
	void Enter(ModulePlayer& player);
	void OnCollision(Collider* my_collider, Collider* other_collider);

private:
	Timer* timer;
};

#endif //__IDLESTATE_H__