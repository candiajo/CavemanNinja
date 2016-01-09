#ifndef __LOOKUPSTATE_H__
#define __LOOKUPSTATE_H__

#include "PlayerState.h"

class LookUpState : public PlayerState
{
public:
	LookUpState();

	PlayerState* update(ModulePlayer& player);
	void enter(ModulePlayer& player);
	void OnCollision(Collider* my_collider, Collider* other_collider);
};

#endif //__LOOKUPSTATE_H__