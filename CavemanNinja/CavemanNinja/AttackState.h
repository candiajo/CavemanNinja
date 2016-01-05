#ifndef __MODULEATTACKSTATE_H__
#define __MODULEATTACKSTATE_H__

#include "DinoState.h"

class Timer;

class AttackState : public DinoState
{
public:
	AttackState(particle_type projectile = FAKE_ATTACK) : projectile(projectile) {};
	~AttackState();
	DinoState* update(ModuleDino& dino);
	void enter(ModuleDino& dino);

private:
	particle_type projectile;
	dino_substate substate;
	Timer* timer;
};

#endif //__MODULEATTACKSTATE_H__