#ifndef __SCAREDSTATE_H__
#define __SCAREDSTATE_H__

#include "PlayerState.h"

class Timer;

class ScaredState : public PlayerState
{
public:
	ScaredState() {};
	~ScaredState();

	PlayerState* Update(ModulePlayer& player);
	void Enter(ModulePlayer& player);
	void OnCollision(Collider* my_collider, Collider* other_collider) {};

private:
	Timer* timer;
};

#endif //__SCAREDSTATE_H__