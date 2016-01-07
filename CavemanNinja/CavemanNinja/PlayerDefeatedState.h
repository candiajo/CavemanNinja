#ifndef __PLAYERDEFEATEDSTATE_H__
#define __PLAYERDEFEATEDSTATE_H__

#include "PlayerState.h"

class IdleState;

class PlayerDefeatedState : public PlayerState
{
public:
	PlayerDefeatedState() {};
	PlayerDefeatedState::PlayerDefeatedState(attack_direction attacked_from) : attacked_from(attacked_from) {}

	PlayerState* update(ModulePlayer& player);
	void enter(ModulePlayer& player);
	void OnCollision(Collider* c1, Collider* c2){};

private:
	attack_direction attacked_from;
};

#endif //__PLAYERDEFEATEDSTATE_H__