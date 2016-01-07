#ifndef __JUMPSTATE_H__
#define __JUMPSTATE_H__

#include "PlayerState.h"

enum jump_substate
{
	NO_FIRE,
	NORMALJUMP,
	SUPERJUMP,
	PRE_DOWNJUMP,
	DOWNJUMP,
	PRE_FALLING,
	FALLING,
	PRE_SHOT_H,
	SHOT_H,
	PRE_SHOT_V,
	SHOT_V
};

class JumpState : public PlayerState
{
public:
	JumpState();
	JumpState(jump_substate substate);

	PlayerState* update(ModulePlayer& player);
	void enter(ModulePlayer& player);
	void OnCollision(Collider* c1, Collider* c2);

private:
	jump_substate substate;
	jump_substate fire;
};

#endif //__JUMPSTATE_H__