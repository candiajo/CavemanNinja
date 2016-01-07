#ifndef __LOOKUPSTATE_H__
#define __LOOKUPSTATE_H__

#include "PlayerState.h"

class LookupState : public PlayerState
{
public:
	LookupState();

	PlayerState* update(ModulePlayer& player);
	void enter(ModulePlayer& player);
	void OnCollision(Collider* c1, Collider* c2){};
};

#endif //__LOOKUPSTATE_H__