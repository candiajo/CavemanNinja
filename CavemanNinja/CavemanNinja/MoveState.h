#ifndef __DINOMOVESTATE_H__
#define __DINOMOVESTATE_H__

#include "DinoState.h"

class MoveState : public DinoState
{
public:
	MoveState(int final_position, particle_type projectile = NO_PARTICLE);

	DinoState* Update(ModuleDino& dino);
	void Enter(ModuleDino& dino);
	void OnCollision(Collider* my_collider, Collider* other_collider);

private:
	int final_position;
	particle_type projectile;
	dino_substate substate;
	int channel;				// of the sound played, for stopping it
};

#endif //__DINOMOVESTATE_H__