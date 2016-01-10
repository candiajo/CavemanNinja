#include "PlayerState.h"
#include "ModuleDino.h"
#include "ModulePlayer.h"
#include "ParticleEnemy.h"
#include "ParticleStone.h"
#include "Application.h"
#include "ModuleCollisions.h"

void PlayerState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	ModulePlayer* player = dynamic_cast<ModulePlayer*>(my_collider->callback);

	if (!player->invulnerable)
	{
		if (my_collider->type == COLLIDER_PLAYER_BODY && other_collider->type != COLLIDER_PROXIMITY)
		{
			Sprite* enemy = dynamic_cast<Sprite*>(other_collider->callback);

			player->hit_received_energy = enemy->damage;
			player->SetInvulnerable(1000);
			if (player->direction == RIGHT) event = PLAYER_HIT_BACK;
			else event = PLAYER_HIT_FRONT;
		}
	}
}

void PlayerState::ThrowParticle(ModulePlayer* player, particle_type weapon)
{
	App->particles->AddParticle(weapon, dynamic_cast<Module*>(player));
}

void PlayerState::RollArm(ModulePlayer* player)
{
	if (player->rolling_arm == false)
		App->particles->AddParticle(ARM, dynamic_cast<Module*>(player));
}

void PlayerState::CheckPosition(ModulePlayer& player)
{
	float y_original = player.position.y;
	int distance = 0;
	Collider* my_collider = player.GetGroundCollider();

	while (!App->collisions->IsCollidingWithGround(*my_collider) && distance <= 10)
	{
		player.position.y++;
		player.PlaceColliders();
		distance++;
	}

	if (distance > 10)
	{
		player.position.y = y_original;
		player.PlaceColliders();
		event = WALK_OFF_PLATFORM;
	}
	else
	{
		player.position.y--;
		player.PlaceColliders();
	}
}