#ifndef __SHOTWEAPONSTATE_H__
#define __SHOTWEAPONSTATE_H__

#include "PlayerState.h"

class ShotWeaponState : public PlayerState
{
public:
	ShotWeaponState() {};
	ShotWeaponState::ShotWeaponState(particle_type weapon) : weapon(weapon) {}

	PlayerState* Update(ModulePlayer& player);
	void Enter(ModulePlayer& player);
	void OnCollision(Collider* my_collider, Collider* other_collider);

private:
	particle_type weapon;
};

#endif //__SHOTWEAPONSTATE_H__