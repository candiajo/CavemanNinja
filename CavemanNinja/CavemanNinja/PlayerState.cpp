#include "PlayerState.h"
#include "ModuleDino.h"
#include "ModulePlayer.h"
#include "ParticleEnemy.h"
#include "ParticleStone.h"

void PlayerState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	Sprite* player = dynamic_cast<Sprite*>(my_collider->callback);

	if (!player->invulnerable)
	{
		if (my_collider->type == COLLIDER_PLAYER_BODY && other_collider->type != COLLIDER_PROXIMITY)
		{
			Sprite* enemy = dynamic_cast<Sprite*>(other_collider->callback);

			player->energy -= enemy->damage;
			player->SetInvulnerable(1000);
			if (player->direction == RIGHT) event = PLAYER_HIT_BACK;
			else event = PLAYER_HIT_FRONT;
		}
	}
}

void PlayerState::Shot(ModulePlayer* player, particle_type weapon)
{
	App->particles->AddParticle(weapon, dynamic_cast<Module*>(player));
}

void PlayerState::RollArm(ModulePlayer* player)
{
	if (player->rolling_arm == false)
		App->particles->AddParticle(ARM, dynamic_cast<Module*>(player));
}