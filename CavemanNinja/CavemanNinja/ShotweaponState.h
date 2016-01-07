#ifndef __SHOTWEAPONSTATE_H__
#define __SHOTWEAPONSTATE_H__

#include "PlayerState.h"

class ShotWeaponState : public PlayerState
{
public:
	ShotWeaponState() {};
	ShotWeaponState::ShotWeaponState(particle_type weapon) : weapon(weapon) {}

	PlayerState* update(ModulePlayer& player);
	void enter(ModulePlayer& player);
	void OnCollision(Collider* c1, Collider* c2){};

private:
	particle_type weapon;
};

#endif //__SHOTWEAPONSTATE_H__