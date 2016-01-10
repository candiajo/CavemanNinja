#include "ModuleAudio.h"
#include "Module.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ParticleArm.h"
#include "Timer.h"
#include "Animation.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"

ParticleArm::ParticleArm(particle_type type, Sprite* generator) : Particle(type, generator)
{
	state = ARM_SLOW_1;
	timer = new Timer(500);
	timer->StartTimer();

	fx_charging = dynamic_cast<ModulePlayer*>(generator)->fx_charging;

	player = dynamic_cast<ModulePlayer*>(generator);

	player->rolling_arm = true;

	arm_slow = new Animation(App->particles->armslow_animation, this);
	arm_fast = new Animation(App->particles->armfast_animation, this);

	channel = App->audio->PlayFx(fx_charging, NO_REPEAT);
	SetCurrentAnimation(arm_slow);
}

ParticleArm::~ParticleArm()
{
	delete arm_slow;
	delete arm_fast;
	delete timer;
}

void ParticleArm::ParticleUpdate()
{
	switch (state)
	{
	case ARM_SLOW_1:
		if (timer->TimeOver())
		{
			timer->StartTimer(500);
			state = ARM_SLOW_2;
			arm_slow->speed *= 2;
		}
		break;
	case ARM_SLOW_2:
		if (timer->TimeOver())
		{
			SetCurrentAnimation(arm_fast);
			timer->StartTimer(750);
			player->charge_enough = true;
			state = ARM_FAST_1;
		}
		break;
	case ARM_FAST_1:
		if (timer->TimeOver())
		{
			timer->StartTimer(2200);
			arm_fast->speed *= 2;
			state = ARM_FAST_2;
		}
		break;
	case ARM_FAST_2:
		if (timer->TimeOver()) state = TIRED;
		break;
	case TIRED:
		player->is_tired = true;
	case ARM_STOP:
		to_destroy = true;
		break;
	}

	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_UP) to_destroy = true;
	
	if (to_destroy)
	{
		player->charge_enough = false;
		player->rolling_arm = false;
		App->audio->StopFxChannel(channel);
		player->arm = nullptr;
	}

	direction = player->direction;

	Point final_position;
	final_position.x = player->position.x;
	final_position.y = player->position.y;

	if (player->is_crouch)
	{
		final_position.y += CROUCH_OFFSET_Y;
		if (direction == RIGHT)	final_position.x += CROUCH_OFFSET_X;
		else					final_position.x -= CROUCH_OFFSET_X;
	}
	else if (player->is_jumping)
		final_position.y += JUMP_OFFSET_Y;
	
	current_frame = &(*current_animation).GetCurrentFrame();
	
	App->renderer->Blit(texture_sprite, (int)final_position.x, (int)final_position.y, current_frame->section, Flip());
}
