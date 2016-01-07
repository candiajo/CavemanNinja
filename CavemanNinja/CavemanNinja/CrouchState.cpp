#include "CrouchState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "ShotcrouchState.h"
#include "TiredState.h"

#include "SDL.h"

CrouchState::CrouchState()
{}

PlayerState* CrouchState::update(ModulePlayer& player)
{
	if (player.is_tired)
	{
		player.is_crouch = false;
		return new TiredState();
	}

	player.is_crouch = false; // will be true if don't change state

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
	else if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_UP)
	{
		player.SetCurrentAnimation(&player.crouch);
	}

	player.is_crouch = true;

	return SAME_STATE;

}

void CrouchState::enter(ModulePlayer& player)
{
	player.is_crouch = true;
	player.x_speed = 0;
	if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT)
	{
		RollArm(&player);
		player.SetCurrentAnimation(&player.crouch, ANGRY_VERSION);
	}
	else
		player.SetCurrentAnimation(&player.crouch);
}