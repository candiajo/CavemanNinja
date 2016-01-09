#ifndef __ATTACKSTATE_H__
#define __ATTACKSTATE_H__

#include "DinoState.h"

class Timer;

class AttackState : public DinoState
{
public:
	AttackState(particle_type projectile = FAKE_ATTACK) : projectile(projectile) {};
	~AttackState();
	DinoState* update(ModuleDino& dino);
	void enter(ModuleDino& dino);
	void OnCollision(Collider* my_collider, Collider* other_collider);

private:
	particle_type projectile;
	dino_substate substate;
	Timer* timer;
};

#endif //__ATTACKSTATE_H__