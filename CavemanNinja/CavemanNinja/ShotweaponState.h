#ifndef __SHOTWEAPONSTATE_H__
#define __SHOTWEAPONSTATE_H__

#include "PlayerState.h"

class ShotWeaponState : public PlayerState
{
public:
	ShotWeaponState() {};
	ShotWeaponState(weapon_subtype weapon_subtype) : weapon_subtype(weapon_subtype) {}

	PlayerState* Update(ModulePlayer& player);
	void Enter(ModulePlayer& player);
	void OnCollision(Collider* my_collider, Collider* other_collider);

private:
	weapon_subtype weapon_subtype;
};

#endif //__SHOTWEAPONSTATE_H__