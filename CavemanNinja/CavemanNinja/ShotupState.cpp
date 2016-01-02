#include "ShotupState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "LookupState.h"

#include "SDL.h"

ShotupState::ShotupState()
{}

PlayerState* ShotupState::update(ModulePlayer& player)
{
	if (player.current_animation->Finished())
	{
		return new LookupState();
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
}