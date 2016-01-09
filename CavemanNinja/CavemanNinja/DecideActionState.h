#ifndef __MODULEDECIDEACTIONSTATE_H__
#define __MODULEDECIDEACTIONSTATE_H__

#include "DinoState.h"

class Timer;

class DecideActionState : public DinoState
{
public:
	~DecideActionState();
	DecideActionState::DecideActionState() {};
	DinoState* update(ModuleDino& dino);
	void enter(ModuleDino& dino);
	void DecideActionState::OnCollision(Collider* my_collider, Collider* other_collider);

private:
	Timer* timer;
};

#endif //__MODULEDECIDEACTIONSTATE_H__