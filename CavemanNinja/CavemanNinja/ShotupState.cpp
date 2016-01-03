#include "ShotupState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "LookupState.h"
#include "ModuleParticles.h"

#include "SDL.h"

ShotupState::ShotupState()
{}

PlayerState* ShotupState::update(ModulePlayer& player)
{
	if (player.current_animation->Finished())
	{
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			return new LookupState();
		else
			return new IdleState();
	}
	else
	{
		return nullptr;
	}
}

void ShotupState::enter(ModulePlayer& player)
{
	player.x_speed = 0;
	player.SetCurrentAnimation(&player.shotup);
	Shot(&player, AXE_VERT);
}