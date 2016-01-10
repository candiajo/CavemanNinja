#ifndef __SHOTCROUCHSTATE_H__
#define __SHOTCROUCHSTATE_H__

#include "PlayerState.h"

class ShotcrouchState : public PlayerState
{
public:
	ShotcrouchState();

	PlayerState* Update(ModulePlayer& player);
	void Enter(ModulePlayer& player);
	void OnCollision(Collider* my_collider, Collider* other_collider);
};

#endif //__SHOTCROUCHSTATE_H__