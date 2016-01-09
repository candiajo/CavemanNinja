#include "ParticleStone.h"
#include "Animation.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "Collider.h"
#include "Timer.h"

#include "ModulePlayer.h"

ParticleStone::ParticleStone(particle_type type, Sprite* generator) : Particle(type, generator)
{
	rollingstone = new Animation(App->particles->rollingstone_animation, this);
	breakingstone = new Animation(App->particles->breakingstone_animation, this);

	energy = 2;
	damage = 5;

	offset.x = 40;
	offset.y = 50;

	SetCurrentAnimation(rollingstone);

	position.x += offset.x;
	position.y += offset.y;

	PlaceColliders();

	if (type == SLOW_STONE) x_speed = 1.5f;
	else if (type == FAST_STONE) x_speed = 3;
	y_speed = 2;

	state = STONE_BOUNCING;
	first_bounce = NO_COLLIDER;

	timer = new Timer(3000);
	timer->StartTimer();

}

ParticleStone::~ParticleStone()
{
	delete rollingstone;
	delete breakingstone;
	delete timer;
}

void ParticleStone::ParticleUpdate()
{
	if (timer->TimeOver() ||
		(state == STONE_BREAKING && breakingstone->Finished()))
		to_destroy = true;
	else
	{
		if (state == STONE_BOUNCING)
		{
			if (y_speed > -0.5 && y_speed < 0) y_speed = 0.5;
			if (y_speed < 0) y_speed *= 0.9f;
			else y_speed *= 1.05f;

			position.y += y_speed;
		}

		if (state != STONE_BREAKING) position.x += x_speed;

		current_frame = &(*current_animation).GetCurrentFrame();
		PlaceColliders();
		App->renderer->Blit(texture_sprite, (int)position.x, (int)position.y, (*current_frame).section, Flip());
	}
}

void ParticleStone::OnCollision(Collider* my_collider, Collider* other_collider)
{
	if (first_bounce == NO_COLLIDER &&
		(other_collider->type == COLLIDER_GROUND || other_collider->type == COLLIDER_PLATFORM))
	{
		first_bounce = other_collider->type;
	}

	// enemy can only collide with the first surface contacted
	if ((other_collider->type == COLLIDER_GROUND || other_collider->type == COLLIDER_PLATFORM) &&
		(other_collider->type == first_bounce || first_bounce == NO_COLLIDER))
	{
		while (my_collider->IsColliding(other_collider))
		{
        	my_collider->rect.y -= 1;
			position.y -= (1.0f / (float)SCREEN_SIZE);
		}

		if (y_speed > 1)
			y_speed /= -4;
		else
		{
			y_speed = 0;
			state = STONE_ROLLING;
		}
	}
	else if (other_collider->type == COLLIDER_PLAYER_SHOT)
	{
		Particle* weapon = dynamic_cast<Particle*>(other_collider->callback);
		
		if (weapon->particle_flag != INNOCUOUS)
		{
			energy -= weapon->damage;
			if (energy <= 0)
			{
				state = STONE_BREAKING;
				SetCurrentAnimation(breakingstone);
			}
		}
	}
	else if (other_collider->type == COLLIDER_PLAYER_ATTACK)
	{
		state = STONE_BREAKING;
		SetCurrentAnimation(breakingstone);
	}
}