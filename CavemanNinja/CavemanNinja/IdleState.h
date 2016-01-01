#ifndef __MODULEIDLESTATE_H__
#define __MODULEIDLESTATE_H__

#include "PlayerState.h"

class CrouchState;

class IdleState : public PlayerState
{
public:
	IdleState();

	PlayerState* update(ModulePlayer& player);
	virtual void enter(ModulePlayer& player);
};

#endif //__MODULEIDLESTATE_H__