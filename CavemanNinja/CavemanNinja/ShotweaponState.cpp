#include "ShotweaponState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "ModuleParticles.h"

#include "SDL.h"

ShotweaponState::ShotweaponState()
{}

PlayerState* ShotweaponState::update(ModulePlayer& player)
{
	if (player.current_animation->Finished())
	{
		return new IdleState();
	}
	else
	{
		return nullptr;
	}
}

void ShotweaponState::enter(ModulePlayer& player)
{
	player.x_speed = 0;
	player.SetCurrentAnimation(&player.shotweapon);
	Shot(&player, AXE_HORZ);
}