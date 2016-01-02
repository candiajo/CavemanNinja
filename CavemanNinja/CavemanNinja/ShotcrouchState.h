#ifndef __MODULESHOTCROUCHSTATE_H__
#define __MODULESHOTCROUCHSTATE_H__

#include "PlayerState.h"

class ShotcrouchState : public PlayerState
{
public:
	ShotcrouchState();

	PlayerState* update(ModulePlayer& player);
	void enter(ModulePlayer& player);
	void OnCollision(Collider* c1, Collider* c2){};
};

#endif //__MODULESHOTCROUCHSTATE_H__