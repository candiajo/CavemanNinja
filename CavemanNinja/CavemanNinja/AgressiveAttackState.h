#ifndef __AGRESSIVEATTACKSTATE_H__
#define __AGRESSIVEATTACKSTATE_H__

#include "DinoState.h"

class AgressiveAttackState : public DinoState
{
public:
	AgressiveAttackState() {};
	DinoState* Update(ModuleDino& dino);
	void Enter(ModuleDino& dino);
	void OnCollision(Collider* my_collider, Collider* other_collider);
};

#endif //__AGRESSIVEATTACKSTATE_H__