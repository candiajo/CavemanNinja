#ifndef __MODULELOOKUPSTATE_H__
#define __MODULELOOKUPSTATE_H__

#include "PlayerState.h"

class LookupState : public PlayerState
{
public:
	LookupState();

	PlayerState* update(ModulePlayer& player);
	void enter(ModulePlayer& player);
	void OnCollision(Collider* c1, Collider* c2){};
};

#endif //__MODULELOOKUPSTATE_H__