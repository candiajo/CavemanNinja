#ifndef __CROUCHSTATE_H__
#define __CROUCHSTATE_H__

#include "PlayerState.h"

class IdleState;

class CrouchState : public PlayerState
{
public:
	CrouchState();

	PlayerState* update(ModulePlayer& player);
	void enter(ModulePlayer& player);
	void OnCollision(Collider* c1, Collider* c2){};
};

#endif //__CROUCHSTATE_H__