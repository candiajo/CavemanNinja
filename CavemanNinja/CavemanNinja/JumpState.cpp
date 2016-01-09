#include "JumpState.h"
#include "IdleState.h"
#include "Collider.h"
#include "AttackedState.h"
#include "TiredState.h"

#include "SDL.h"

JumpState::JumpState()
{}

JumpState::JumpState(jump_substate substate) : substate(substate)
{}

PlayerState* JumpState::update(ModulePlayer& player)
{
	if (event == PLAYER_HIT_BACK) 
		return new AttackedState(ATTACKED_FROM_BEHIND);
	else if (event == PLAYER_HIT_FRONT) 
		return new AttackedState(ATTACKED_FROM_FRONT);

	if (player.is_tired)
	{
		player.x_speed = 0;
		return new TiredState();
	}

	if (event == PLAYER_STEP_GROUND)
		return new IdleState();

	if (event == PLAYER_STEP_ENEMY)
		return new JumpState(MICROJUMP);

	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_UP && player.rolling_arm)
	{
		if (player.charge_enough) fire = PRE_SHOT_SUPER;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		//todelete &&		limit != LEFT)
	{
		player.direction = LEFT;
		player.x_speed = -DEFAULT_X_SPEED;
	}
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		// todelete &&		limit != RIGHT)
	{
		player.direction = RIGHT;
		player.x_speed = DEFAULT_X_SPEED;
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP ||
		App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		player.x_speed = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT &&
			substate != SUPERJUMP)
			fire = PRE_SHOT_V;
		else
			fire = PRE_SHOT_H;
	}
	
	switch (fire)
	{
		case PRE_SHOT_SUPER:
			player.SetCurrentAnimation(&player.supershot);
			Shot(&player, SUPER_AXE);
			fire = SHOT_H;
			break;
		case PRE_SHOT_H:
			if (substate != SUPERJUMP)
			{
				player.SetCurrentAnimation(&player.shotweapon);
			}
			Shot(&player, AXE_HORZ);
			fire = SHOT_H;
			break;

		case SHOT_H:
			if (player.current_animation->Finished())
			{
				if (player.y_speed > 0)
					player.SetCurrentAnimation(&player.downjump);
				else if (substate != SUPERJUMP)
					player.SetCurrentAnimation(&player.normaljump);

				if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_REPEAT)
				{
					RollArm(&player);
					player.SetCurrentAnimation(player.current_animation, ANGRY_VERSION);
				}
				fire = NO_FIRE;
			}
			break;

		case PRE_SHOT_V:
			player.SetCurrentAnimation(&player.shotup);
			Shot(&player, AXE_VERT);
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

				if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_REPEAT)
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
			player.y_speed *= 0.91f;
			if (player.y_speed > -0.4)
			{
				player.y_speed = 0.5;
				substate = PRE_FALLING;
			}
			break;

		case SUPERJUMP:
			player.y_speed *= 0.92f;
			if (player.y_speed > -0.25)
			{
				player.y_speed = 0.45f;
				substate = PRE_FALLING;
			}
			break;

		case PRE_FALLING:
		case PRE_DOWNJUMP:
			if (fire == NO_FIRE)
				if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_REPEAT)
					player.SetCurrentAnimation(&player.downjump, ANGRY_VERSION);
				else
					player.SetCurrentAnimation(&player.downjump);
			substate = FALLING;
			break;

		case FALLING:
		case DOWNJUMP:
			player.y_speed *= 1.08f;
			break;
	}
		
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_UP)
	{
		player.SetCurrentAnimation(player.current_animation);
	}
	return SAME_STATE;
}

void JumpState::enter(ModulePlayer& player)
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
		player.y_speed = NORMAL_JUMP_SPEED;
		player.SetCurrentAnimation(&player.normaljump);
		break;
	case SUPERJUMP:
		player.y_speed = -8;// SUPER_JUMP_SPEED;
		player.SetCurrentAnimation(&player.superjump);
		break;
	case DOWNJUMP:
	case FALLING:
		player.y_speed = 0.4f;// DOWN_JUMP_SPEED;
		player.SetCurrentAnimation(&player.downjump);
		break;
	}

	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_REPEAT)
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
	else if (my_collider->type == COLLIDER_DETECT_GROUND &&
		     other_collider->type != COLLIDER_BORDER)
	{
		while (my_collider->IsColliding(other_collider))
		{
			my_collider->rect.y-= 1;
			player->position.y -= 1.0f / (float)SCREEN_SIZE;
		}

		player->is_jumping = false;
		event = PLAYER_STEP_GROUND;
	}
	if ((substate == DOWNJUMP || substate == FALLING) &&
		(my_collider->type == COLLIDER_DETECT_GROUND && other_collider->type == COLLIDER_ENEMY))
	{
		event = PLAYER_STEP_ENEMY;
	}

}
