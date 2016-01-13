#include "ParticleEnemy.h"
#include "Animation.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "Collider.h"
#include "Timer.h"
#include "ModuleAudio.h"
#include "ModuleDino.h"
#include "ModulePlayer.h"

ParticleEnemy::ParticleEnemy(particle_type type, Sprite* generator) : Particle(type, generator)
{
	rollingenemy = new Animation(App->particles->rollingenemy_animation, this);
	hitenemy = new Animation(App->particles->hitenemy_animation, this);
	defeatedenemy = new Animation(App->particles->defeatedenemy_animation, this);

	fx_enemy_hurt = dynamic_cast<ModuleDino*>(generator)->fx_enemy_hurt;
	fx_weapon_hit= dynamic_cast<ModuleDino*>(generator)->fx_weapon_hit;

	energy = 1;
	damage = 5;

	offset.x = 40;
	offset.y = 50;

	SetCurrentAnimation(rollingenemy);

	position.x += offset.x;
	position.y += offset.y;

	PlaceColliders();

	direction = RIGHT;

	x_speed = 1.75;
	y_speed = 1;

	state = ENEMY_BOUNCING;
	first_bounce = NO_COLLIDER;

	timer = new Timer(6000);
	timer->StartTimer();
}

ParticleEnemy::~ParticleEnemy()
{
	RELEASE(rollingenemy);
	RELEASE(hitenemy);
	RELEASE(defeatedenemy);
	RELEASE(timer);
}

void ParticleEnemy::ParticleUpdate()
{
	if (timer->TimeOver()) to_destroy = true;
	else
	{
		switch (state)
		{
		case ENEMY_BOUNCING:
			y_speed += 0.1f;
			position.y += y_speed;
			break;
		case ENEMY_HIT:
			first_bounce = NO_COLLIDER;
			y_speed += 0.1f;
			position.y += y_speed;
			if (bounces == 3)
			{
				x_speed = 0;
				y_speed = 0;
				timer->StartTimer(1000);
				SetCurrentAnimation(defeatedenemy);
				state = ENEMY_DEFEATED;
			}
			break;
		}

		position.x += x_speed;

		current_frame = &(*current_animation).GetCurrentFrame();
		PlaceColliders();
		App->renderer->Blit(texture_sprite, (int)position.x, (int)position.y, current_frame->section, Flip());
	}
}

void ParticleEnemy::OnCollision(Collider* my_collider, Collider* other_collider)
{
	if (first_bounce == NO_COLLIDER &&
		(other_collider->type == COLLIDER_GROUND || other_collider->type == COLLIDER_PLATFORM))
	{
		first_bounce = other_collider->type;
	}

	// live enemy can only collide with the first surface contacted
	if ((other_collider->type == COLLIDER_GROUND || other_collider->type == COLLIDER_PLATFORM) &&
		(other_collider->type == first_bounce || first_bounce == NO_COLLIDER))
	{
		while (my_collider->IsColliding(other_collider))
		{
			position.y--;
			PlaceColliders();
		}

		bounces++;
		y_speed /= -2.0f;
	}
	else if (state == ENEMY_BOUNCING)
	{
		if (other_collider->type == COLLIDER_PLAYER_ATTACK)
		{
			Sprite* player = dynamic_cast<Sprite*>(other_collider->callback);

			bounces = 0;
			position.y -= 7;	// for avoiding ground collision in the first hit frame
			if (player->direction == RIGHT)
			{
				direction = LEFT;
				x_speed = +1.5f;
			}
			else
			{
				direction = RIGHT;
				x_speed = -1.5f;
			}
			y_speed = -2.5f;

			state = ENEMY_HIT;
			App->player1->score += 300;
			App->audio->PlayFx(fx_enemy_hurt);
			SetCurrentAnimation(hitenemy);
		}
		else if (other_collider->type == COLLIDER_PLAYER_SHOT)
		{
			Particle* weapon = dynamic_cast<Particle*>(other_collider->callback);

			if (weapon->particle_flag != INNOCUOUS)	// axe on ground, for example
			{
				bounces = 0;
				position.y -= 7;	// for avoiding ground collision in the first hit frame
				if (weapon->direction == RIGHT)
				{
					direction = LEFT;
					x_speed = +1.5f;
				}
				else
				{
					direction = RIGHT;
					x_speed = -1.5f;
				}
				y_speed = -2.5f;

				if (weapon->subtype == SUPER)
				{
					x_speed *= 1.5f;
					y_speed *= 1.5f;
					App->particles->AddParticle(WOMP, weapon);
				}
				else if (weapon->subtype == VERTICAL) App->particles->AddParticle(WAM_V, weapon);
				else App->particles->AddParticle(WAM_H, weapon); // HORIZONTAL or CROUCH

				state = ENEMY_HIT;
				App->audio->PlayFx(fx_weapon_hit);
				App->audio->PlayFx(fx_enemy_hurt);
				weapon->particle_flag = INNOCUOUS;
				App->player1->score += 300;
				SetCurrentAnimation(hitenemy);
			}
		}
	}
}