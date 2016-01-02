#include "ShotcrouchState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "CrouchState.h"

#include "SDL.h"

ShotcrouchState::ShotcrouchState()
{}

PlayerState* ShotcrouchState::update(ModulePlayer& player)
{
	if (player.current_animation->Finished())
	{
		return new CrouchState();
	}
	else
	{
		return nullptr;
	}
}

void ShotcrouchState::enter(ModulePlayer& player)
{
	player.x_speed = 0;
	player.SetCurrentAnimation(&player.shotcrouch);
}