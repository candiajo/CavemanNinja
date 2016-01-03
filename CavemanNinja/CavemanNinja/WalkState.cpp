#include "WalkState.h"
#include "IdleState.h"
#include "CrouchState.h"
#include "Collider.h"
#include "JumpState.h"
#include "ShotweaponState.h"

WalkState::WalkState()
{}

PlayerState* WalkState::update(ModulePlayer& player)
{
	Direction limit;

	if (event == WALK_OFF_PLATFORM)
	{
		return new JumpState(DOWNJUMP);
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP ||
		App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		return new IdleState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		return new CrouchState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
	{
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			return new JumpState(SUPERJUMP);
		else
			return new JumpState(NORMALJUMP);
	}
	else if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		return new ShotweaponState();
	}
	else
	{
		limit = ScreenLimitReached(player);

		if (player.direction == LEFT && limit != LEFT)
		{
			player.x_speed = -DEFAULT_X_SPEED;
		}
		else if (player.direction == RIGHT && limit != RIGHT)
		{
			player.x_speed = DEFAULT_X_SPEED;
		}
		else player.x_speed = 0;
	}
	return nullptr;
}

void WalkState::enter(ModulePlayer& player)
{
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		player.direction = LEFT;
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		player.direction = RIGHT;

	player.SetCurrentAnimation(&player.walk);
}



void WalkState::OnCollision(Collider* c1, Collider* c2)
{
	ModulePlayer* player = dynamic_cast<ModulePlayer*>(c1->callback);

	if (c1->type == COLLIDER_PLAYER_GROUND &&
		c2->type == COLLIDER_BORDER)
	{
		event = WALK_OFF_PLATFORM;
	}
}