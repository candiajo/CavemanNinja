#ifndef __TIREDTATE_H__
#define __TIREDTATE_H__

#include "PlayerState.h"

class Timer;

class TiredState : public PlayerState
{
public:
	TiredState() {};
	~TiredState();

	PlayerState* Update(ModulePlayer& player);
	void Enter(ModulePlayer& player);
	void OnCollision(Collider* my_collider, Collider* other_collider);

private:
	Timer* timer;
	ModulePlayer* player;
};

#endif //__TIREDTATE_H__