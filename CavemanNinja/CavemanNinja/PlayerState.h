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
	virtual void OnCollision(Collider* c1, Collider* c2) = 0;

protected:
	game_events event;

	type_direction ScreenLimitReached(ModulePlayer& player)
	{
		if (player.position.x <= LEFT_LIMIT) return LEFT;
		if (player.position.x >= RIGHT_LIMIT) return RIGHT;

		return NONE;
	}

	void Shot(ModulePlayer* player, particle_type weapon)
	{
		App->particles->AddParticle(weapon, dynamic_cast<Module*>(player));
	}

	void RollArm(ModulePlayer* player)
	{
		if (player->rolling_arm == false)
			App->particles->AddParticle(ARM, dynamic_cast<Module*>(player));
	}
};

#endif //__PLAYERSTATE_H__