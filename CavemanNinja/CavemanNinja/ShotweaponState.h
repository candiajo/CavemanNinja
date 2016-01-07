#ifndef __SHOTWEAPONSTATE_H__
#define __SHOTWEAPONSTATE_H__

#include "PlayerState.h"

class ShotweaponState : public PlayerState
{
public:
	ShotweaponState();

	PlayerState* update(ModulePlayer& player);
	void enter(ModulePlayer& player);
	void OnCollision(Collider* c1, Collider* c2){};
};

#endif //__SHOTWEAPONSTATE_H__