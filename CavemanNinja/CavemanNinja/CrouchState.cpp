#include "CrouchState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "ShotcrouchState.h"

#include "SDL.h"

CrouchState::CrouchState()
{}

PlayerState* CrouchState::update(ModulePlayer& player)
{
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		return new IdleState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_DOWN &&
		     player.position.y < 150)	// for avoiding downjump from the ground
	{
		return new JumpState(DOWNJUMP);
	}
	else if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_DOWN)
	{
		return new ShotcrouchState();
	}
	else
	{
		return nullptr;
	}
}

void CrouchState::enter(ModulePlayer& player)
{
	player.x_speed = 0;
	player.SetCurrentAnimation(&player.crouch);
}