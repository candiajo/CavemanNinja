#ifndef __AGRESSIVEATTACKSTATE_H__
#define __AGRESSIVEATTACKSTATE_H__

#include "DinoState.h"

class AgressiveAttackState : public DinoState
{
public:
	AgressiveAttackState() {};
	DinoState* update(ModuleDino& dino);
	void enter(ModuleDino& dino);
};

#endif //__AGRESSIVEATTACKSTATE_H__