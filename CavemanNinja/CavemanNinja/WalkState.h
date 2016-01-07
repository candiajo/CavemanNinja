#ifndef __WALKSTATE_H__
#define __WALKSTATE_H__

#include "Globals.h"
#include "PlayerState.h"

#include "SDL.h"

class WalkState : public PlayerState
{
public:
	WalkState();

	PlayerState* update(ModulePlayer& player);
	void enter(ModulePlayer& player);
	void OnCollision(Collider* c1, Collider* c2);
};

#endif //__WALKSTATE_H__