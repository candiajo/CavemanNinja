#ifndef __MODULESHOTUPSTATE_H__
#define __MODULESHOTUPSTATE_H__

#include "PlayerState.h"

class ShotupState : public PlayerState
{
public:
	ShotupState();

	PlayerState* update(ModulePlayer& player);
	void enter(ModulePlayer& player);
	void OnCollision(Collider* c1, Collider* c2){};
};

#endif //__MODULESHOTUPSTATE_H__