#include "LookupState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "ShotupState.h"
#include "WalkState.h"
#include "TiredState.h"

#include "SDL.h"

LookupState::LookupState()
{}

PlayerState* LookupState::update(ModulePlayer& player)
{
	if (player.is_tired) return new TiredState();

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
	{
		return new IdleState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_DOWN)
	{
		return new JumpState(SUPERJUMP);
	}
	else if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_DOWN)
	{
		return new ShotupState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT ||
		App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		return new WalkState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_UP)
	{
		player.SetCurrentAnimation(&player.lookup);
	}
		return SAME_STATE;
}

void LookupState::enter(ModulePlayer& player)
{
	player.x_speed = 0;
	if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT)
	{
		RollArm(&player);
		player.SetCurrentAnimation(&player.lookup, ANGRY_VERSION);
	}
	else
		player.SetCurrentAnimation(&player.lookup);
}