#ifndef __PLAYERDEFEATEDSTATE_H__
#define __PLAYERDEFEATEDSTATE_H__

#include "PlayerState.h"

class IdleState;
class Timer;

class PlayerDefeatedState : public PlayerState
{
public:
	PlayerDefeatedState() {};
	PlayerDefeatedState(attack_direction attacked_from) : attacked_from(attacked_from) {}
	~PlayerDefeatedState();

	PlayerState* update(ModulePlayer& player);
	void enter(ModulePlayer& player);
	void OnCollision(Collider* my_collider, Collider* other_collider){};

private:
	attack_direction attacked_from;
	Timer* timer;
};

#endif //__PLAYERDEFEATEDSTATE_H__