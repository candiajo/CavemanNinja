#ifndef __MODULEAGRESSIVEATTACKSTATE_H__
#define __MODULEAGRESSIVEATTACKSTATE_H__

#include "DinoState.h"

class AgressiveAttackState : public DinoState
{
public:
	AgressiveAttackState() {};
	DinoState* update(ModuleDino& dino);
	void enter(ModuleDino& dino);
};

#endif //__MODULEAGRESSIVEATTACKSTATE_H__