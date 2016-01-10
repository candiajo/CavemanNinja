#include "DinoState.h"
#include "Particle.h"
#include "Globals.h"
#include "DinoDefeatedState.h"
#include "SuperHitState.h"
#include "ModuleAudio.h"
#include "ModuleDino.h"

void DinoState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	if (other_collider->type == COLLIDER_PLAYER_SHOT)
	{
		Sprite* dino = dynamic_cast<Sprite*>(my_collider->callback);
		Particle* weapon = dynamic_cast<Particle*>(other_collider->callback);

		if (weapon->particle_flag != INNOCUOUS && !dino->invulnerable)
		{
			App->audio->PlayFx(App->dino->fx_weapon_hit);
			dino->energy -= weapon->damage;
			if (dino->energy <= 0)
			{
				event = DINO_IS_DEFEATED;
			}
			else if (weapon->type == SUPER_AXE) event = DINO_GET_SUPERHIT;
			else event = DINO_GET_HIT;
			dino->SetInvulnerable(1500);
			weapon->particle_flag = INNOCUOUS;	// for not colliding with any other collider in the same frame
		}
	}
}

void DinoState::ThrowParticle(ModuleDino* dino, particle_type projectile)
{
	App->particles->AddParticle(projectile, dynamic_cast<Module*>(dino));
}

float DinoState::Y_variation()
{
	if (abs(total_y_variation) >= 0.5f) y_variation *= -1.0f;
	total_y_variation += y_variation;
	return total_y_variation;
}