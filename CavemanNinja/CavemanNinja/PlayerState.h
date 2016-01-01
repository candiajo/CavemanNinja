#ifndef __MODULEPLAYERSTATE_H__
#define __MODULEPLAYERSTATE_H__

#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "Application.h"

class PlayerState
{
public:
	//PlayerState() {}
	virtual ~PlayerState() {};
	virtual PlayerState* update(ModulePlayer& player) = 0;
	virtual void enter(ModulePlayer& player) = 0;
};

#endif //__MODULEPLAYERSTATE_H__