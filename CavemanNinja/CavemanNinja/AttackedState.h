#ifndef __ATTACKEDSTATE_H__
#define __ATTACKEDSTATE_H__

#include "PlayerState.h"

enum attacked_substate
{
	BOUNCE,
	ON_GROUND
};

class Timer;

class AttackedState : public PlayerState
{
public:
	AttackedState() {};
	AttackedState(attack_direction attacked_from) : attacked_from(attacked_from) {}
	~AttackedState();

	PlayerState* Update(ModulePlayer& player);
	void Enter(ModulePlayer& player);
	void OnCollision(Collider* my_collider, Collider* other_collider);

private:
	Timer* timer;
	int initial_y;
	int move;
	attacked_substate substate;
	attack_direction attacked_from;
};

#endif //__ATTACKEDSTATE_H__