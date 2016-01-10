#include "ParticleAxe.h"
#include "Animation.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "Collider.h"
#include "Timer.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"

ParticleAxe::ParticleAxe(particle_type type, Sprite* generator) : Particle(type, generator)
{
	int modifier;

	timer = new Timer(3000);
	timer->StartTimer();

	fx_player_superattack = dynamic_cast<ModulePlayer*>(generator)->fx_player_superattack;
	fx_player_attack = dynamic_cast<ModulePlayer*>(generator)->fx_player_attack;

	if (direction == LEFT)
		modifier = -1;
	else if (direction == RIGHT)
		modifier = 1;

	if (type == SUPER_AXE)
	{
		delay = new Timer(100);
		x_speed = 3.0f;
		damage = 3;
		offset.x = 55;
		offset.y = -15;
		distance_straight = 60;
		first_state = AXE_FORWARD;
		axe = new Animation(App->particles->superaxe_animation, this);
	}
	else // normal axe
	{
		delay = new Timer(0);
		if (type == AXE_HORZ)
		{
			x_speed = 2.0f;
			first_state = AXE_FORWARD;
			offset.x = 55;
			offset.y = 15;
		}
		else if (type == AXE_CROUCH)
		{
			x_speed = 2.0f;
			first_state = AXE_FORWARD;
			offset.x = 55;
			offset.y = 28;
		}
		else if (type == AXE_VERT)
		{
			x_speed = 0.0f;
			offset.x = 35;
			offset.y = 0;
			y_speed = -6;
			first_state = AXE_UP;
		}

		damage = 1;
		distance_straight = 30;
		axe = new Animation(App->particles->axe_animation, this);
	}

	x_speed *= (float)modifier;
		
	SetCurrentAnimation(axe);

	if (direction == LEFT)
		offset.x = (generator->current_frame->section->w - axe->frames.front().section->w - offset.x);

	position.x += offset.x;
	position.y += offset.y;

	PlaceColliders();

	delay->StartTimer();
}

ParticleAxe::~ParticleAxe()
{
	RELEASE(axe);
	RELEASE(timer);
	RELEASE(delay);
}

void ParticleAxe::ParticleUpdate()
{
	switch (state)
	{
	case AXE_WAITING_DELAY:
		if (delay->TimeOver())
		{
			App->audio->PlayFx(fx_player_attack, NO_REPEAT);
			if (type == SUPER_AXE) App->audio->PlayFx(fx_player_superattack, NO_REPEAT);
			state = first_state;
		}
		break;
	case AXE_FORWARD:
		if (distance_straight <= 0)
		{
			y_speed = 1.2f;
			if (type == SUPER_AXE) x_speed /= 2.0f;
			state = AXE_FALLING_FORWARD;
		}
		break;

	case AXE_FALLING_FORWARD:
		y_speed *= 1.08f;
		break;

	case AXE_UP:
		if (y_speed > -0.4f)
		{
			y_speed = 0.4f;
			state = AXE_FALLING_DOWN;
		}
		else
			y_speed *= 0.92f;
		break;

	case AXE_FALLING_DOWN:
		y_speed *= 1.08f;
		break;

	case AXE_LAST_MOMENT:
		if (timer->TimeOver()) to_destroy = true;
	}

	if (state != AXE_LAST_MOMENT)
	{
		position.y += y_speed;
		position.x += x_speed;

		distance_straight -= (int)abs(x_speed);

		PlaceColliders();
	}

	if (state != AXE_WAITING_DELAY)
	{
		if (state != AXE_LAST_MOMENT) current_frame = &(*current_animation).GetCurrentFrame();
		App->renderer->Blit(texture_sprite, (int)position.x, (int)position.y, current_frame->section, Flip());
	}

	previous_frame = current_frame;
}

void ParticleAxe::OnCollision(Collider* my_collider, Collider* other_collider)
{
	if (state != AXE_LAST_MOMENT)
	{
		if (my_collider->type == COLLIDER_DETECT_GROUND)
		{
			if (other_collider->type == COLLIDER_PLATFORM &&
				(state == AXE_UP || state == AXE_FORWARD))
			{
			}// there is no collision in this situation
			else if (other_collider->type == COLLIDER_GROUND ||
				other_collider->type == COLLIDER_PLATFORM)
			{
				particle_flag = INNOCUOUS;
				//todelete state = AXE_ON_GROUND;
				state = AXE_LAST_MOMENT;
				timer->StartTimer(250);
				LOG("250")
					current_frame = &(*current_animation).PeekFrame(6 - 1);
			}
		}
		else if (my_collider->type == COLLIDER_PLAYER_SHOT &&
			(other_collider->type == COLLIDER_ENEMY || other_collider->type == COLLIDER_DINO))
		{
			timer->StartTimer(40);
			current_frame = &(*current_animation).PeekFrame(6 - 1);
			state = AXE_LAST_MOMENT;
		}
	}
}