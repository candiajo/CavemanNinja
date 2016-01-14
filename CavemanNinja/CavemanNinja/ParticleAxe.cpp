#include "ParticleAxe.h"
#include "Animation.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "Collider.h"
#include "Timer.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleDino.h"

ParticleAxe::ParticleAxe(particle_type type, Sprite* generator) : Particle(type, generator)
{
	int modifier;

	timer = new Timer(3000);
	timer->StartTimer();

	ModulePlayer* player = dynamic_cast<ModulePlayer*>(generator);

	player->weapons_on_screen++;

	fx_player_superattack = player->fx_player_superattack;
	fx_player_attack = player->fx_player_attack;

	if (direction == LEFT)
		modifier = -1;
	else if (direction == RIGHT)
		modifier = 1;

	if (type == SUPER_AXE)
	{
		subtype = SUPER;
		delay = new Timer(100);
		x_speed = 3.0f;
		damage = 3;
		offset.x = 55;
		offset.y = -15;
		distance_straight = 60;
		first_state = AXE_FORWARD;
		axe_animation = new Animation(App->particles->superaxe_animation, this);
	}
	else // normal axe
	{
		delay = new Timer(0);
		if (type == AXE_HORZ)
		{
			subtype = HORIZONTAL;
			x_speed = 1.8f;
			first_state = AXE_FORWARD;
			offset.x = 55;
			offset.y = 15;
		}
		else if (type == AXE_CROUCH)
		{
			subtype = CROUCH;
			x_speed = 2.0f;
			first_state = AXE_FORWARD;
			offset.x = 55;
			offset.y = 28;
		}
		else if (type == AXE_VERT)
		{
			subtype = VERTICAL;
			x_speed = 0.0f;
			offset.x = 35;
			offset.y = 0;
			y_speed = -2.3f;
			first_state = AXE_UP;
		}

		damage = 1;
		distance_straight = 30;
		axe_animation = new Animation(App->particles->axe_animation, this);
	}

	x_speed *= (float)modifier;
		
	SetCurrentAnimation(axe_animation);

	if (direction == LEFT)
		offset.x = (generator->current_frame->section->w - axe_animation->frames.front().section->w - offset.x);

	position.x += offset.x;
	position.y += offset.y;

	PlaceColliders();

	delay->StartTimer();
}

ParticleAxe::~ParticleAxe()
{
	RELEASE(axe_animation);
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
			App->audio->PlayFx(fx_player_attack);
			if (type == SUPER_AXE) App->audio->PlayFx(fx_player_superattack);
			state = first_state;
		}
		break;
	case AXE_FORWARD:
		if (distance_straight <= 0)
		{
			y_speed = 1.2f;
			if (type == SUPER_AXE) x_speed /= 2.0f;
			state = AXE_FALLING;
		}
		break;

	case AXE_FALLING:
	case AXE_UP:
		y_speed += 0.1f;
		position.y += y_speed;

		if (y_speed >= 0) state = AXE_FALLING;
		break;

	case AXE_LAST_MOMENT:
		if (timer->TimeOver())
		{
			App->player1->weapons_on_screen--;
			to_destroy = true;
		}
	}

	if (state != AXE_LAST_MOMENT)
	{
		position.y += y_speed;
		position.x += x_speed;

		distance_straight -= abs(x_speed);

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
				(state == AXE_UP || state == AXE_FORWARD || state == AXE_WAITING_DELAY))
			{}// there is no collision in this situation
			else if (other_collider->type == COLLIDER_GROUND ||
				other_collider->type == COLLIDER_PLATFORM)
			{
				particle_flag = INNOCUOUS;
				state = AXE_LAST_MOMENT;
				timer->StartTimer(250);
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