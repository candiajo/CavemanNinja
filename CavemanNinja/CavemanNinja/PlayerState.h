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
	virtual PlayerState* Update(ModulePlayer& player) = 0;
	virtual void Enter(ModulePlayer& player) = 0;
	void CheckPosition(ModulePlayer& player);
	virtual void OnCollision(Collider* my_collider, Collider* other_collider) = 0;

	game_events event;

protected:
	void ThrowParticle(ModulePlayer* player, particle_type weapon) const;
	void RollArm(ModulePlayer* player) const;
};

#endif //__PLAYERSTATE_H__