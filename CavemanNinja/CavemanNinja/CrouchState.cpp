#include "CrouchState.h"
#include "IdleState.h"

#include "SDL.h"

CrouchState::CrouchState()
{}

PlayerState* CrouchState::update(ModulePlayer& player)
{
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		return new IdleState();
	}
	else
	{
		return nullptr;
	}
}

void CrouchState::enter(ModulePlayer& player)
{
	player.x_speed = 0;
	player.current_animation = &player.crouch;
}