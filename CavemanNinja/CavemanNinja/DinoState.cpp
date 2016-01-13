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

		// decide which hit particle to show
		if (weapon->particle_flag != INNOCUOUS)
		{
			if (dino->invulnerable)
			{
				App->particles->AddParticle(HIT_DINO, weapon);
			}
			else
			{
				if (weapon->subtype == SUPER) App->particles->AddParticle(WOMP, weapon);
				else if (weapon->subtype == VERTICAL) App->particles->AddParticle(WAM_V, weapon);
				else App->particles->AddParticle(WAM_H, weapon); // HORIZONTAL or CROUCH
			}
		}

		if (weapon->particle_flag != INNOCUOUS && !dino->invulnerable)
		{
			App->audio->PlayFx(App->dino->fx_weapon_hit);
			dino->energy -= weapon->damage;
			if (dino->energy <= 0)
			{
				event = DINO_IS_DEFEATED;
			}
			else if (weapon->subtype == SUPER)
			{
				dino->SetInvulnerable(3000);
				event = DINO_GET_SUPERHIT;
			}
			else
			{
				dino->SetInvulnerable(1000);
				event = DINO_GET_HIT;
			}
			weapon->particle_flag = INNOCUOUS;	// for not colliding with any other collider in the same frame
		}
	}
}

void DinoState::ThrowParticle(ModuleDino* dino, particle_type projectile) const
{
	App->particles->AddParticle(projectile, dynamic_cast<Module*>(dino));
}

float DinoState::Y_variation()
{
	if (abs(total_y_variation) >= 0.5f) y_variation *= -1.0f;
	total_y_variation += y_variation;
	return total_y_variation;
}

const int DinoState::GetRandomPosition() const
{
	int random_number;

	srand(SDL_GetTicks());

	random_number = rand() % 100 + 1;

	if (random_number <= 45) return(FAR_POSITION);
	else if (random_number <= 75)  return(MIDDLE_POSITION);
	else return(NEAR_POSITION);
}