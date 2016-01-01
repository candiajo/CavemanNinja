#ifndef __MODULEWALKSTATE_H__
#define __MODULEWALKSTATE_H__

#include "Globals.h"
#include "PlayerState.h"

#include "SDL.h"

class IdleState;



class WalkState : public PlayerState
{
public:
	WalkState();

	PlayerState* update(ModulePlayer& player);
	virtual void enter(ModulePlayer& player);

private:
	Direction direction;
};

#endif //__MODULEWALKSTATE_H__