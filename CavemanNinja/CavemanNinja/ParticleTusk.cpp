#include "ParticleTusk.h"
#include "Animation.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "Collider.h"
#include "Timer.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleDino.h"

ParticleTusk::ParticleTusk(particle_type type, Sprite* generator) : Particle(type, generator)
{
	int modifier;

	ModulePlayer* player = dynamic_cast<ModulePlayer*>(generator);

	player->weapons_on_screen++;

	fx_player_superattack = player->fx_player_superattack;
	fx_player_attack = player->fx_player_attack;

	if (direction == LEFT)
		modifier = -1;
	else if (direction == RIGHT)
		modifier = 1;

	tusk_animation = new Animation(App->particles->tusk_animation, this);
	SetCurrentAnimation(tusk_animation);

	if (type == SUPER_TUSK)
	{
		subtype = SUPER;
		timer = new Timer(400);
		delay = new Timer(100);
		x_speed = 6.0f;
		damage = 3;
		offset.x = 20;
		offset.y = 15;
		first_state = TUSK_FORWARD;
		current_frame = &current_animation->PeekFrame(2);
	}
	else // normal tusk
	{
		timer = new Timer(300);
		delay = new Timer(0);
		if (type == TUSK_HORZ)
		{
			subtype = HORIZONTAL;
			x_speed = 4.5f;
			first_state = TUSK_FORWARD;
			offset.x = 55;
			offset.y = 20;
			current_frame = &current_animation->PeekFrame(0);
		}
		else if (type == TUSK_CROUCH)
		{
			subtype = CROUCH;
			x_speed = 4.5f;
			first_state = TUSK_FORWARD;
			offset.x = 55;
			offset.y = 33;
			current_frame = &current_animation->PeekFrame(0);
		}
		else if (type == TUSK_VERT)
		{
			subtype = VERTICAL;
			x_speed = 0.0f;
			offset.x = 35;
			offset.y = 0;
			y_speed = -4.5f;
			first_state = TUSK_UP;
			current_frame = &current_animation->PeekFrame(1);
		}

		damage = 1;
	}
	
	timer->StartTimer();

	x_speed *= (float)modifier;

	if (direction == LEFT)
		offset.x = (generator->current_frame->section->w - tusk_animation->frames.front().section->w - offset.x);

	position.x += offset.x;
	position.y += offset.y;

	RefreshColliders();
	PlaceColliders();

	delay->StartTimer();
}

ParticleTusk::~ParticleTusk()
{
	RELEASE(tusk_animation);
	RELEASE(timer);
	RELEASE(delay);
}

void ParticleTusk::ParticleUpdate()
{
	if (timer->TimeOver())
	{
		App->player1->weapons_on_screen--;
		to_destroy = true;
	}
	else
	{
		switch (state)
		{
		case TUSK_WAITING_DELAY:
			if (delay->TimeOver())
			{
				App->audio->PlayFx(fx_player_attack);
				if (type == SUPER_TUSK) App->audio->PlayFx(fx_player_superattack);
				state = first_state;
			}
			break;

		case TUSK_FORWARD:
		case TUSK_UP:
			break;

		case TUSK_LAST_MOMENT:
			if (timer->TimeOver())
			{
				App->player1->weapons_on_screen--;
				to_destroy = true;
			}
		}

		if (state != TUSK_LAST_MOMENT)
		{
			position.y += y_speed;
			position.x += x_speed;

			PlaceColliders();
		}

		if (state != TUSK_WAITING_DELAY)
		{
			App->renderer->Blit(texture_sprite, (int)position.x, (int)position.y, current_frame->section, Flip());
		}

		previous_frame = current_frame;
	}
}

void ParticleTusk::OnCollision(Collider* my_collider, Collider* other_collider)
{
	if (state != TUSK_LAST_MOMENT)
	{
		if (other_collider->type == COLLIDER_ENEMY || other_collider->type == COLLIDER_DINO)
		{
			timer->StartTimer(40);
			state = TUSK_LAST_MOMENT;
		}
	}
}