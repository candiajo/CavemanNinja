#ifndef __MODULEDECIDEACTIONSTATE_H__
#define __MODULEDECIDEACTIONSTATE_H__

#include "DinoState.h"

class Timer;

class DecideActionState : public DinoState
{
public:
	DecideActionState() {};
	~DecideActionState();
	DinoState* Update(ModuleDino& dino);
	void Enter(ModuleDino& dino);
	void DecideActionState::OnCollision(Collider* my_collider, Collider* other_collider);

private:
	Timer* timer;
};

#endif //__MODULEDECIDEACTIONSTATE_H__