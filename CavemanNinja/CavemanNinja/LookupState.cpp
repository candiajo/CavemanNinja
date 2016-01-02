#include "LookupState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "ShotupState.h"
#include "WalkState.h"

#include "SDL.h"

LookupState::LookupState()
{}

PlayerState* LookupState::update(ModulePlayer& player)
{
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
	{
		return new IdleState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
	{
		return new JumpState(SUPERJUMP);
	}
	else if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		return new ShotupState();
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

void LookupState::enter(ModulePlayer& player)
{
	player.x_speed = 0;
	player.SetCurrentAnimation(&player.lookup);
}