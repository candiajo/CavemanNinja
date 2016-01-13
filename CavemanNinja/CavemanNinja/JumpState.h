#ifndef __JUMPSTATE_H__
#define __JUMPSTATE_H__

#include "PlayerState.h"

enum jump_substate
{
	NO_FIRE,
	MICROJUMP,
	NORMALJUMP,
	SUPERJUMP,
	DOWNJUMP,
	PRE_FALLING,
	FALLING,
	PRE_SHOT_SUPER,
	PRE_SHOT_H,
	SHOT_H,
	PRE_SHOT_V,
	SHOT_V
};

class JumpState : public PlayerState
{
public:
	JumpState() {};
	JumpState(jump_substate substate) : substate(substate) {};

	PlayerState* Update(ModulePlayer& player);
	void Enter(ModulePlayer& player);
	void OnCollision(Collider* my_collider, Collider* other_collider);

private:
	jump_substate substate;
	jump_substate fire;
};

#endif //__JUMPSTATE_H__