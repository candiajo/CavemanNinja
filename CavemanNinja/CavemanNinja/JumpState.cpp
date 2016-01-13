#include "ModuleAudio.h"
#include "JumpState.h"
#include "IdleState.h"
#include "Collider.h"
#include "AttackedState.h"
#include "TiredState.h"

#include "SDL.h"

PlayerState* JumpState::Update(ModulePlayer& player)
{
	switch (event)
	{
	case PLAYER_STEP_GROUND:
		App->audio->PlayFx(player.fx_player_land);
		return new IdleState();
		break;
	case PLAYER_STEP_ENEMY:
		ThrowParticle(&player, KUP);
		return new JumpState(MICROJUMP);
		break;
	case PLAYER_HIT_FRONT:
		return new AttackedState(ATTACKED_FROM_FRONT);
		break;
	case PLAYER_HIT_BACK:
		return new AttackedState(ATTACKED_FROM_BEHIND);
		break;
	}

	if (player.is_tired)
	{
		player.x_speed = 0;
		return new TiredState();
	}

	if (App->input->GetKey(FIRE_BUTTON) == KEY_UP && player.rolling_arm)
	{
		if (player.charge_enough) fire = PRE_SHOT_SUPER;
	}

	if (App->input->GetKey(LEFT_BUTTON) == KEY_REPEAT)
	{
		player.direction = LEFT;
		player.x_speed = -DEFAULT_X_SPEED;
	}
	else if (App->input->GetKey(RIGHT_BUTTON) == KEY_REPEAT)
	{
		player.direction = RIGHT;
		player.x_speed = DEFAULT_X_SPEED;
	}
	else if (App->input->GetKey(LEFT_BUTTON) == KEY_UP ||
		App->input->GetKey(RIGHT_BUTTON) == KEY_UP)
	{
		player.x_speed = 0;
	}

	if (App->input->GetKey(FIRE_BUTTON) == KEY_DOWN &&
		(fire != SHOT_V && fire != SHOT_H))
	{
		if (App->input->GetKey(UP_BUTTON) == KEY_REPEAT &&
			substate != SUPERJUMP)
			fire = PRE_SHOT_V;
		else
			fire = PRE_SHOT_H;
	}
	
	switch (fire)
	{
		case PRE_SHOT_SUPER:
			player.SetCurrentAnimation(&player.supershot);
			ThrowParticle(&player, player.GetCurrentWeapon(SUPER));
			fire = SHOT_H;
			break;

		case PRE_SHOT_H:
			if (substate != SUPERJUMP)
			{
				if (player.weapons_on_screen < 2) player.SetCurrentAnimation(&player.shotweapon);
				else player.SetCurrentAnimation(&player.shotnoweapon);
			}
			if (player.weapons_on_screen < 2) ThrowParticle(&player, player.GetCurrentWeapon(HORIZONTAL));
			fire = SHOT_H;
			break;

		case SHOT_H:
			if (player.current_animation->Finished())
			{
				if (player.y_speed > 0)
					player.SetCurrentAnimation(&player.downjump);
				else if (substate != SUPERJUMP)
					player.SetCurrentAnimation(&player.normaljump);

				if (App->input->GetKey(FIRE_BUTTON) == KEY_REPEAT)
				{
					RollArm(&player);
					player.SetCurrentAnimation(player.current_animation, ANGRY_VERSION);
				}
				fire = NO_FIRE;
			}
			break;

		case PRE_SHOT_V:
			if (player.weapons_on_screen < 2)
			{
				player.SetCurrentAnimation(&player.shotup);
				ThrowParticle(&player, player.GetCurrentWeapon(VERTICAL));
			}
			else player.SetCurrentAnimation(&player.shotupnw);
			fire = SHOT_V;
			break;

		case SHOT_V:
			if (player.current_animation->Finished())
			{
				fire = NO_FIRE;
				if (player.y_speed > 0)
					player.SetCurrentAnimation(&player.downjump);
				else
					player.SetCurrentAnimation(&player.normaljump);

				if (App->input->GetKey(FIRE_BUTTON) == KEY_REPEAT)
				{
					RollArm(&player);
					player.SetCurrentAnimation(player.current_animation, ANGRY_VERSION);
				}
			}
			break;
	}

	switch (substate)
	{
		case NORMALJUMP:
		case SUPERJUMP:
			if (player.y_speed >= 0.7f) substate = PRE_FALLING;
			//no break;
		case FALLING:
		case DOWNJUMP:
			player.y_speed += 0.08f;
			player.position.y += player.y_speed;
			break;

		case PRE_FALLING:
			if (fire == NO_FIRE)
				if (App->input->GetKey(FIRE_BUTTON) == KEY_REPEAT)
					player.SetCurrentAnimation(&player.downjump, ANGRY_VERSION);
				else
					player.SetCurrentAnimation(&player.downjump);
			substate = FALLING;
			break;
	}
		
	if (App->input->GetKey(FIRE_BUTTON) == KEY_UP)
	{
		player.SetCurrentAnimation(player.current_animation);
	}
	return SAME_STATE;
}

void JumpState::Enter(ModulePlayer& player)
{
	fire = NO_FIRE;
	player.is_jumping = true;

	if (substate == SUPERJUMP && player.rolling_arm) substate = NORMALJUMP;

	switch (substate)
	{
	case MICROJUMP:
		player.y_speed = -1;
		player.SetCurrentAnimation(&player.normaljump);
		player.current_animation->SetLastFrame();
		substate = NORMALJUMP;
		break;
	case NORMALJUMP:
		player.y_speed = -2.2f;
		player.SetCurrentAnimation(&player.normaljump);
		App->audio->PlayFx(player.fx_player_jump);
		break;
	case SUPERJUMP:
		player.y_speed = -2.8f;
		player.SetCurrentAnimation(&player.superjump);
		App->audio->PlayFx(player.fx_super_jump);
		break;
	case DOWNJUMP:
	case FALLING:
		player.y_speed = 0.2f;
		player.SetCurrentAnimation(&player.downjump);
		break;
	}

	if (App->input->GetKey(FIRE_BUTTON) == KEY_REPEAT)
	{
		RollArm(&player);
		player.SetCurrentAnimation(player.current_animation, ANGRY_VERSION);
	}
}

void JumpState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	PlayerState::OnCollision(my_collider, other_collider);

	ModulePlayer* player = dynamic_cast<ModulePlayer*>(my_collider->callback);

	if (substate == DOWNJUMP && other_collider->type == COLLIDER_PLATFORM)
	{
		// jumping down the platform, nothing to do
	}
	else if (my_collider->type == COLLIDER_DETECT_GROUND)
	{
		while (my_collider->IsColliding(other_collider))
		{
			player->position.y -= 1.0f;
			player->PlaceColliders();
		}

		player->is_jumping = false;
		event = PLAYER_STEP_GROUND;
	}
	
	if ((substate == DOWNJUMP || substate == FALLING) &&
		(my_collider->type == COLLIDER_PLAYER_ATTACK && other_collider->type == COLLIDER_ENEMY))
	{
		player->hit_received_energy = 0;	// to prevent same frame hit with the enemy stepped
		event = PLAYER_STEP_ENEMY;
	}

}
