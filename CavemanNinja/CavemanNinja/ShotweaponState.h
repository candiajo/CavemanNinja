#ifndef __MODULESHOTWEAPONSTATE_H__
#define __MODULESHOTWEAPONSTATE_H__

#include "PlayerState.h"

class ShotweaponState : public PlayerState
{
public:
	ShotweaponState();

	PlayerState* update(ModulePlayer& player);
	void enter(ModulePlayer& player);
	void OnCollision(Collider* c1, Collider* c2){};
};

#endif //__MODULESHOTWEAPONSTATE_H__