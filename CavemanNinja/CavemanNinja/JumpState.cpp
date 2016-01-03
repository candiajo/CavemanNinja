#include "JumpState.h"
#include "IdleState.h"
#include "Collider.h"

#include "SDL.h"

JumpState::JumpState()
{}

JumpState::JumpState(jump_substate substate) : substate(substate)
{}

PlayerState* JumpState::update(ModulePlayer& player)
{
	Direction limit = ScreenLimitReached(player);

	if (event == PLAYER_STEP_GROUND)
		return new IdleState();

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		player.direction = LEFT;
		player.x_speed = -DEFAULT_X_SPEED;
	}
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		player.direction = RIGHT;
		player.x_speed = DEFAULT_X_SPEED;
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP ||
		App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		player.x_speed = 0;
	}

	if (limit == RIGHT || limit == LEFT) player.x_speed = 0;

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
		case PRE_SHOT_H:
			if (substate != SUPERJUMP)
			{
				//debug
				Shot(&player, STONE);
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
				fire = NO_FIRE;
			if (player.y_speed > 0)
				player.SetCurrentAnimation(&player.downjump);
			else
				player.SetCurrentAnimation(&player.normaljump);
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
				player.y_speed = 0.45;
				substate = PRE_FALLING;
			}
			break;

		case PRE_FALLING:
		case PRE_DOWNJUMP:
			if (fire == NO_FIRE)
				player.SetCurrentAnimation(&player.downjump);
			substate = FALLING;
			break;

		case FALLING:
		case DOWNJUMP:
			player.y_speed *= 1.08f;
			break;
	}
		
	return nullptr;

}

void JumpState::enter(ModulePlayer& player)
{
	fire = NO_FIRE;

	switch (substate)
	{
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
}

void JumpState::OnCollision(Collider* c1, Collider* c2)
{
	ModulePlayer* player = dynamic_cast<ModulePlayer*>(c1->callback);

	if (substate == DOWNJUMP && c2->type == COLLIDER_PLATFORM)
	{
		// jumping down the platform, nothing to do
	}
	else if (c1->type == COLLIDER_PLAYER_GROUND &&
		     c2->type != COLLIDER_BORDER)
	{
		while (c1->IsColliding(c2))
		{
			c1->rect.y-= 1;
			player->position.y -= 1.0f / (float)SCREEN_SIZE;
		}

		event = PLAYER_STEP_GROUND;
	}
}