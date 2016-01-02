#ifndef __MODULECROUCHSTATE_H__
#define __MODULECROUCHSTATE_H__

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

#endif //__MODULECROUCHSTATE_H__