#include "AttackedState.h"
#include "IdleState.h"
#include "PlayerDefeatedState.h"
#include "Timer.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

AttackedState::~AttackedState()
{
	delete timer;
}

PlayerState* AttackedState::update(ModulePlayer& player)
{
	switch (substate)
	{
	case BOUNCE:
		player.y_speed += 0.1f;
		player.position.y += player.y_speed;
		break;
	case ON_GROUND:
		player.y_speed = 0;
		if (player.energy <= 0)
		{
			if (attacked_from == ATTACKED_FROM_BEHIND) return new PlayerDefeatedState(ATTACKED_FROM_BEHIND);
			else return new PlayerDefeatedState(ATTACKED_FROM_FRONT);
		}
		else
		{
			player.is_hit = false;
			return new IdleState();
		}
	}

	if (substate != ON_GROUND)
	{
		player.position.x += move;
	}
	return SAME_STATE;
}

void AttackedState::enter(ModulePlayer& player)
{
	timer = new Timer(600);
	timer->StartTimer();
	initial_y = (int)player.position.y;

	player.x_speed = 0;
	player.y_speed = -1.2f;
	
	player.energy -= player.hit_received_energy;
	player.hit_received_energy = 0;

	substate = BOUNCE;
	if (attacked_from == ATTACKED_FROM_FRONT)
	{
		player.SetCurrentAnimation(&player.frontattack);
		if (player.direction == LEFT) move = +1;
		else move = -1;
	}
	else
	{
		player.SetCurrentAnimation(&player.backattack);
		if (player.direction == LEFT) move = -1;
		else move = +1;
	}

	player.is_hit = true;
	player.StopArm();
	App->audio->PlayFx(App->player1->fx_player_hurt);
}

void AttackedState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	ModulePlayer* player = dynamic_cast<ModulePlayer*>(my_collider->callback);
	if (player->y_speed > 0)
	{
		if (other_collider->type == COLLIDER_GROUND || other_collider->type == COLLIDER_PLATFORM)
		{
			while (my_collider->IsColliding(other_collider))
			{
				my_collider->rect.y -= 1;
				player->position.y -= 1.0f / (float)SCREEN_SIZE;
			}
			substate = ON_GROUND;
		}
	}
}