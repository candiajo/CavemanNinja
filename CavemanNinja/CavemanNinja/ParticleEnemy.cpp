#include "ParticleEnemy.h"
#include "Animation.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "Collider.h"
#include "Timer.h"

#include "ModulePlayer.h"

ParticleEnemy::ParticleEnemy(particle_type type, Sprite* generator) : Particle(type, generator)
{
	rollingenemy = new Animation(App->particles->rollingenemy_animation, this);
	hitenemy = new Animation(App->particles->hitenemy_animation, this);

	life = 1;
	damage = 4;

	offset.x = 40;
	offset.y = 50;

	SetCurrentAnimation(rollingenemy);

	position.x += offset.x;
	position.y += offset.y;

	x_speed = 1.75;
	y_speed = 1;

	state = ENEMY_BOUNCING;
	first_bounce = NO_COLLIDER;

	timer = new Timer(3000);
	timer->StartTimer();
}

ParticleEnemy::~ParticleEnemy()
{
	delete rollingenemy;
	delete hitenemy;
	delete timer;
}

void ParticleEnemy::ParticleUpdate()
{
	if (timer->TimeOver() ||
		(state == ENEMY_HIT && hitenemy->Finished()))
		to_destroy = true;
	else
	{
		if (state == ENEMY_BOUNCING)
		{
			if (y_speed > -0.5 && y_speed < 0) y_speed = 0.5;
			if (y_speed < 0) y_speed *= 0.95f;
			else y_speed *= 1.05f;

			position.y += y_speed;
		}

		if (state != ENEMY_HIT) position.x += x_speed;

		current_frame = &(*current_animation).GetCurrentFrame();
		PlaceColliders();
		App->renderer->Blit(texture_sprite, (int)position.x, (int)position.y, current_frame->section, Flip());
	}
}

void ParticleEnemy::OnCollision(Collider* c1, Collider* c2)
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

		y_speed /= -2.75f;
	}
	else if (c2->type == COLLIDER_PLAYER_SHOT)
	{
		Particle* weapon = dynamic_cast<Particle*>(c2->callback);

		life -= weapon->damage;
		if (life <= 0)
		{
			state = ENEMY_HIT;
			SetCurrentAnimation(hitenemy);
		}
	}
}