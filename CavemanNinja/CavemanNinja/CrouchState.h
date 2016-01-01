#ifndef __MODULECROUCHSTATE_H__
#define __MODULECROUCHSTATE_H__

#include "PlayerState.h"

class IdleState;

class CrouchState : public PlayerState
{
public:
	CrouchState();

	PlayerState* update(ModulePlayer& player);
	virtual void enter(ModulePlayer& player);
};

#endif //__MODULECROUCHSTATE_H__