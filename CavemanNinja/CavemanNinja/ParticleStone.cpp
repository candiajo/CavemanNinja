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

	life = 2;
	damage = 5;

	offset.x = 40;
	offset.y = 50;

	SetCurrentAnimation(rollingstone);

	position.x += offset.x;
	position.y += offset.y;

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

void ParticleStone::OnCollision(Collider* c1, Collider* c2)
{
	if (first_bounce == NO_COLLIDER &&
		(c2->type == COLLIDER_GROUND || c2->type == COLLIDER_PLATFORM))
	{
		first_bounce = c2->type;
	}

	// enemy can only collide with the first surface contacted
	if ((c2->type == COLLIDER_GROUND || c2->type == COLLIDER_PLATFORM) &&
		(c2->type == first_bounce || first_bounce == NO_COLLIDER))
	{
		while (c1->IsColliding(c2))
		{
        	c1->rect.y -= 1;
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
	else if (c2->type == COLLIDER_PLAYER_SHOT)
	{
		Particle* weapon = dynamic_cast<Particle*>(c2->callback);
		
		life -= weapon->damage;
		if (life <= 0)
		{
			state = STONE_BREAKING;
			SetCurrentAnimation(breakingstone);
		}
	}
}