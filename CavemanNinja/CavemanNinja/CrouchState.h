#ifndef __CROUCHSTATE_H__
#define __CROUCHSTATE_H__

#include "PlayerState.h"

class IdleState;

class CrouchState : public PlayerState
{
public:
	CrouchState() {};

	PlayerState* Update(ModulePlayer& player);
	void Enter(ModulePlayer& player);
	void OnCollision(Collider* my_collider, Collider* other_collider);
};

#endif //__CROUCHSTATE_H__