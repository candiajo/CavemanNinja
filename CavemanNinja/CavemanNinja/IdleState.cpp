#include "IdleState.h"
#include "CrouchState.h"
#include "WalkState.h"
#include "JumpState.h"
#include "LookupState.h"
#include "ShotweaponState.h"
#include "AttackedState.h"

#include "SDL.h"

IdleState::IdleState() : PlayerState()
{}

PlayerState* IdleState::update(ModulePlayer& player)
{
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) // debug
	{
		return new AttackedState(ATTACKED_FROM_FRONT);
	}
	if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN) // debug
	{
		return new AttackedState(ATTACKED_FROM_BEHIND);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		return new CrouchState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT ||
		     App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		return new WalkState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_DOWN &&
		     App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		return new JumpState(SUPERJUMP);
	}
	else if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_DOWN)
	{
		return new JumpState(NORMALJUMP);
	}
	else if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		return new LookupState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_DOWN)
	{
		return new ShotweaponState();
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
	player.SetCurrentAnimation(&player.idle);
}