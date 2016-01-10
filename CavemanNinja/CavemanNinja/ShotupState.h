#ifndef __SHOTUPSTATE_H__
#define __SHOTUPSTATE_H__

#include "PlayerState.h"

class ShotupState : public PlayerState
{
public:
	ShotupState();

	PlayerState* Update(ModulePlayer& player);
	void Enter(ModulePlayer& player);
	void OnCollision(Collider* my_collider, Collider* other_collider);
};

#endif //__SHOTUPSTATE_H__