#include "WalkState.h"
#include "IdleState.h"
#include "CrouchState.h"

#include "SDL.h"

WalkState::WalkState()
{}

PlayerState* WalkState::update(ModulePlayer& player)
{
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
		if (direction == LEFT)
		{
			player.x_speed = -WALK_SPEED;
		}
		else
		{
			player.x_speed = WALK_SPEED;
		}
		return nullptr;
	}
}

void WalkState::enter(ModulePlayer& player)
{
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		direction = LEFT;
	else
		direction = RIGHT;

	player.current_animation = &player.walk;
	player.current_animation->Reset();
}