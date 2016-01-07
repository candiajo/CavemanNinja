#ifndef __ATTACKEDSTATE_H__
#define __ATTACKEDSTATE_H__

#include "PlayerState.h"

enum attacked_substate
{
	MOVE_UP,
	MOVE_DOWN,
	ON_GROUND
};

class Timer;

class AttackedState : public PlayerState
{
public:
	AttackedState() {};
	AttackedState(attack_direction attacked_from) : attacked_from(attacked_from) {}
	~AttackedState();

	PlayerState* update(ModulePlayer& player);
	void enter(ModulePlayer& player);
	void OnCollision(Collider* c1, Collider* c2);

private:
	Timer* timer;
	int initial_y;
	int move;
	attacked_substate substate;
	attack_direction attacked_from;
};

#endif //__ATTACKEDSTATE_H__