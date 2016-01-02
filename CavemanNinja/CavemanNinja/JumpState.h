#ifndef __MODULEJUMPSTATE_H__
#define __MODULEJUMPSTATE_H__

#include "PlayerState.h"

class JumpState : public PlayerState
{
public:
	JumpState();
	JumpState(jump_substate substate);

	PlayerState* update(ModulePlayer& player);
	void enter(ModulePlayer& player);
	void OnCollision(Collider* c1, Collider* c2);

	jump_substate substate;
	jump_substate fire;
};

#endif //__MODULEJUMPSTATE_H__