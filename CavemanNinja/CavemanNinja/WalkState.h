#ifndef __WALKSTATE_H__
#define __WALKSTATE_H__

#include "Globals.h"
#include "PlayerState.h"

#include "SDL.h"

class WalkState : public PlayerState
{
public:
	WalkState();

	PlayerState* Update(ModulePlayer& player);
	void Enter(ModulePlayer& player);
	void OnCollision(Collider* my_collider, Collider* other_collider);
};

#endif //__WALKSTATE_H__