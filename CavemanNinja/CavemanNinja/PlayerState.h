#ifndef __PLAYERSTATE_H__
#define __PLAYERSTATE_H__

#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "Application.h"
#include "ModuleParticles.h"

class PlayerState
{
public:
	virtual ~PlayerState() {};
	virtual PlayerState* update(ModulePlayer& player) = 0;
	virtual void enter(ModulePlayer& player) = 0;
	virtual void OnCollision(Collider* my_collider, Collider* other_collider) = 0;

protected:
	game_events event;

	void Shot(ModulePlayer* player, particle_type weapon);

	void RollArm(ModulePlayer* player);
};

#endif //__PLAYERSTATE_H__