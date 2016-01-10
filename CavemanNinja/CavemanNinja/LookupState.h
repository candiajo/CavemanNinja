#ifndef __LOOKUPSTATE_H__
#define __LOOKUPSTATE_H__

#include "PlayerState.h"

class LookUpState : public PlayerState
{
public:
	LookUpState();

	PlayerState* Update(ModulePlayer& player);
	void Enter(ModulePlayer& player);
	void OnCollision(Collider* my_collider, Collider* other_collider);
};

#endif //__LOOKUPSTATE_H__