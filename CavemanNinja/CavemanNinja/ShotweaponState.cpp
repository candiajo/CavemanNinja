#include "ShotWeaponState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "ModuleParticles.h"

#include "SDL.h"

PlayerState* ShotWeaponState::update(ModulePlayer& player)
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

void ShotWeaponState::enter(ModulePlayer& player)
{
	player.x_speed = 0;

	if (weapon == SUPER_AXE) player.SetCurrentAnimation(&player.supershot);
	else player.SetCurrentAnimation(&player.shotweapon);
	Shot(&player, weapon);
}