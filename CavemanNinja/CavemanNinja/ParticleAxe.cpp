#include "ParticleAxe.h"
#include "Animation.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "Collider.h"
#include "Timer.h"

ParticleAxe::ParticleAxe(particle_type type, Sprite* generator) : Particle(type, generator)
{
	if (type == SUPER_AXE)
	{
		offset.x = 55;
		offset.y = 0;
		distance_straight = 100;
		axe = new Animation(App->particles->superaxe_animation, this);
	}
	else
	{
		distance_straight = 20;
		axe = new Animation(App->particles->axe_animation, this);
	}
	
	SetCurrentAnimation(axe);

	if (type == AXE_HORZ)
	{
		state = AXE_FORWARD;
		offset.x = 55;
		offset.y = 13;
	}
	
	if (type == AXE_CROUCH)
	{
		state = AXE_FORWARD;
		offset.x = 55;
		offset.y = 28;
	}

	if (type == AXE_VERT)			// vertical shot
	{
		offset.x = 35;
		offset.y = 0;
		y_speed = -6;
		state = AXE_UP;
	}
	else if (direction == LEFT)		// horizontal shot (normal or super)
		x_speed = -1.5f;
	else if (direction == RIGHT)
		x_speed = 1.5f;

	if (direction == LEFT)
		offset.x = (generator->current_frame->section.w - axe->frames.front().section.w - offset.x);

	position.x += offset.x;
	position.y += offset.y;
}

ParticleAxe::~ParticleAxe()
{
	axe->DestroyColliders();
	//axe->colliders.front()->to_destroy = true;	// destroy the only collider of axe
	delete axe;
	delete timer;
}

void ParticleAxe::ParticleUpdate()
{
	if (state != AXE_ON_GROUND)
		current_frame = &(*current_animation).GetCurrentFrame();

	switch (state)
	{
	case AXE_FORWARD:
		if (distance_straight <= 0)
		{
			y_speed = 0.5f;
			state = AXE_FALLING_FORWARD;
		}
		break;

	case AXE_FALLING_FORWARD:
		y_speed *= 1.08f;
		break;

	case AXE_UP:
		if(y_speed > -0.4)
		{
			y_speed = 0.5;
			state = AXE_FALLING_DOWN;
		}
		else
			y_speed *= 0.92f;
		break;

	case AXE_FALLING_DOWN:
		y_speed *= 1.08f;
		break;

	case AXE_ON_GROUND:
		if (timer->TimeOver())
			to_destroy = true;
	}

	if (state != AXE_ON_GROUND)
	{
		position.y += y_speed;
		position.x += x_speed;

		distance_straight -= abs(x_speed);

		PlaceColliders();
	}

	App->renderer->Blit(texture_sprite, (int)position.x, (int)position.y, &(*current_frame).section, Flip());

	previous_frame = current_frame;
}

void ParticleAxe::OnCollision(Collider* c1, Collider* c2)
{
	if (state != AXE_ON_GROUND)
	{
		if (c2->type == COLLIDER_PLATFORM &&
			(state == AXE_UP || state == AXE_FORWARD))
		{
		}// there is no collision in this situation
		else if (c2->type == COLLIDER_GROUND ||
			c2->type == COLLIDER_PLATFORM)
		{
			state = AXE_ON_GROUND;
			timer = new Timer(250);
			timer->StartTimer();
			current_frame = &(*current_animation).PeekFrame(6 - 1);
		}
		else
			to_destroy = true;
	}
}