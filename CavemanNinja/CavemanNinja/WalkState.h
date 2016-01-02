#ifndef __MODULEWALKSTATE_H__
#define __MODULEWALKSTATE_H__

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

private:
	Direction ScreenLimitReached(ModulePlayer& player);
};

#endif //__MODULEWALKSTATE_H__