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

	offset.x = 50;
	offset.y = 50;

	SetCurrentAnimation(rollingstone);

	position.x += offset.x;
	position.y += offset.y;

	if (type == STONE) x_speed = App->var1; // 5;
	else if (type == FAST_STONE) x_speed = App->var3;//10;
	y_speed = App->var2;// 0.8f;

	state = STONE_BOUNCING;

	timer = new Timer(3000);
	timer->StartTimer();
}

ParticleStone::~ParticleStone()
{
	rollingstone->DestroyColliders();
	breakingstone->DestroyColliders();

	delete rollingstone;
	delete breakingstone;
}

void ParticleStone::ParticleUpdate()
{
	if (timer->TimeOver()) 
		to_destroy = true;
	else
	{
		if (state == STONE_BOUNCING)
		{
			if (y_speed > -0.5 && y_speed < 0) y_speed = 0.5;
			if (y_speed < 0) y_speed *= 0.92f;
			else y_speed *= 1.08f;

			position.y += y_speed;
		}

		position.x += x_speed;

		current_frame = &(*current_animation).GetCurrentFrame();
		PlaceColliders();
		App->renderer->Blit(texture_sprite, (int)position.x, (int)position.y, &(*current_frame).section, Flip());
	}
}

void ParticleStone::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_GROUND)
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
}