#include "WalkState.h"
#include "IdleState.h"
#include "CrouchState.h"

WalkState::WalkState()
{}

PlayerState* WalkState::update(ModulePlayer& player)
{
	Direction limit;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP ||
		App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		return new IdleState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		return new CrouchState();
	}
	else
	{
		limit = ScreenLimitReached(player);

		if (player.direction == LEFT && limit != LEFT)
		{
			player.x_speed = -WALK_SPEED;
		}
		else if (player.direction == RIGHT && limit != RIGHT)
		{
			player.x_speed = WALK_SPEED;
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

	player.current_animation = &player.walk;
	player.current_animation->Reset();
}

Direction WalkState::ScreenLimitReached(ModulePlayer& player)
{
	if (player.position.x <= LEFT_LIMIT) return LEFT;
	if (player.position.x >= RIGHT_LIMIT) return RIGHT;

	//LOG("x: %f", player.position.x);
	return NONE;
}