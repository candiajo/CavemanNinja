#ifndef __DINOMOVESTATE_H__
#define __DINOMOVESTATE_H__

#include "DinoState.h"

class MoveState : public DinoState
{
public:
	MoveState(int final_position, particle_type projectile = NO_PARTICLE);
	DinoState* update(ModuleDino& dino);
	void enter(ModuleDino& dino);
	void OnCollision(Collider* my_collider, Collider* other_collider);

private:
	int final_position;
	particle_type projectile;
	dino_substate substate;
};

#endif //__DINOMOVESTATE_H__