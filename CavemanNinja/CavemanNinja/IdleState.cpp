#include "IdleState.h"
#include "CrouchState.h"
#include "WalkState.h"

#include "SDL.h"

IdleState::IdleState() : PlayerState()
{}

PlayerState* IdleState::update(ModulePlayer& player)
{
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		return new CrouchState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT ||
		     App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		return new WalkState();
	}
	else
	{
		return nullptr;
	}
}

void IdleState::enter(ModulePlayer& player)
{
	player.x_speed = 0;
	player.y_speed = 0;
	player.current_animation = &player.idle;
}