#include "ParticleWheel.h"
#include "Animation.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "Collider.h"
#include "Timer.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleDino.h"

ParticleWheel::ParticleWheel(particle_type type, Sprite* generator) : Particle(type, generator)
{
	int modifier;

	hits = 0;

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

	if (type == SUPER_WHEEL)
	{
		subtype = SUPER;
		delay = new Timer(100);
		x_speed = 3.0f;
		damage = 3;
		offset.x = 20;
		offset.y = -25;
		distance_straight = 35;
		first_state = WHEEL_FLY_FORWARD;
		wheel = new Animation(App->particles->superwheel_animation, this);
	}
	else // normal wheel
	{
		delay = new Timer(0);
		if (type == WHEEL_HORZ)
		{
			subtype = HORIZONTAL;
			x_speed = 1.8f;
			first_state = WHEEL_FLY_FORWARD;
			offset.x = 50;
			offset.y = 5;
		}
		else if (type == WHEEL_CROUCH)
		{
			subtype = CROUCH;
			x_speed = 2.0f;
			first_state = WHEEL_FLY_FORWARD;
			offset.x = 50;
			offset.y = 13;
		}
		else if (type == WHEEL_VERT)
		{
			subtype = VERTICAL;
			x_speed = 0.0f;
			offset.x = 35;
			offset.y = 0;
			y_speed = -2.0f;
			first_state = WHEEL_UP;
		}

		damage = 2;
		distance_straight = 15;
		wheel = new Animation(App->particles->wheel_animation, this);
	}

	x_speed *= (float)modifier;

	SetCurrentAnimation(wheel);

	if (direction == LEFT)
		offset.x = (generator->current_frame->section->w - wheel->frames.front().section->w - offset.x);

	position.x += offset.x;
	position.y += offset.y;

	PlaceColliders();

	delay->StartTimer();
}

ParticleWheel::~ParticleWheel()
{
	RELEASE(wheel);
	RELEASE(timer);
	RELEASE(delay);
}

void ParticleWheel::ParticleUpdate()
{
	switch (state)
	{
	case WHEEL_WAITING_DELAY:
		if (delay->TimeOver())
		{
			App->audio->PlayFx(fx_player_attack);
			if (type == SUPER_WHEEL) App->audio->PlayFx(fx_player_superattack);
			state = first_state;
		}
		break;

	case WHEEL_FLY_FORWARD:
		if (distance_straight <= 0)
		{
			y_speed = 1.4f;
			//if (type == SUPER_WHEEL) x_speed /= 2.0f;
			state = WHEEL_FALLING;
		}
		break;

	case WHEEL_FALLING:
		position.y += y_speed;
		break;

	case WHEEL_UP:
		if (y_speed >= 0) state = WHEEL_DOWN;
		//no break;
	case WHEEL_DOWN:
		y_speed += 0.1f;
		position.y += y_speed;
		break;
		
	case WHEEL_ROLLING:
	case WHEEL_LAST_MOMENT:
		if (timer->TimeOver())
		{
			App->player1->weapons_on_screen--;
			to_destroy = true;
		}
	}

	if (state != WHEEL_LAST_MOMENT)
	{
		position.y += y_speed;
		position.x += x_speed;

		distance_straight -= abs(x_speed);

		PlaceColliders();
	}

	if (state != WHEEL_WAITING_DELAY)
	{
		if (state != WHEEL_LAST_MOMENT) current_frame = &(*current_animation).GetCurrentFrame();
		App->renderer->Blit(texture_sprite, (int)position.x, (int)position.y, current_frame->section, Flip());
	}

	if (position.x > SCREEN_WIDTH || position.x < -100)	// off screen
	{
		timer->StartTimer(1);
		state = WHEEL_LAST_MOMENT;
	}

	previous_frame = current_frame;
}

void ParticleWheel::OnCollision(Collider* my_collider, Collider* other_collider)
{
	if (state != WHEEL_LAST_MOMENT)
	{
		if (my_collider->type == COLLIDER_DETECT_GROUND)
		{
			if (other_collider->type == COLLIDER_PLATFORM &&
				(state == WHEEL_UP || state == WHEEL_FLY_FORWARD || state == WHEEL_WAITING_DELAY))
			{
			}// there is no collision in this situation
			else if (other_collider->type == COLLIDER_GROUND ||
				other_collider->type == COLLIDER_PLATFORM)
			{
				if (state != WHEEL_ROLLING && state != WHEEL_DOWN)
				{
					y_speed = 1.0f;
					state = WHEEL_ROLLING;
				}
				else while (my_collider->IsColliding(other_collider))
				{
					position.y--;
					PlaceColliders();
				}

				if (state == WHEEL_DOWN) 
				{
					timer->StartTimer(40);
					current_frame = &(*current_animation).PeekFrame(4 - 1);
					state = WHEEL_LAST_MOMENT;
				}
			}
		}
		else if (my_collider->type == COLLIDER_PLAYER_SHOT &&
			(other_collider->type == COLLIDER_ENEMY || other_collider->type == COLLIDER_DINO))
		{
			hits++;
			if (other_collider->type == COLLIDER_DINO ||
				(other_collider->type == COLLIDER_ENEMY && hits == 2))
			{
				timer->StartTimer(40);
				current_frame = &(*current_animation).PeekFrame(4 - 1);
				state = WHEEL_LAST_MOMENT;
			}
		}
	}
}