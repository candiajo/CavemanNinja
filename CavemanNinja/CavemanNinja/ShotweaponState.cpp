#include "ShotWeaponState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "ModuleParticles.h"
#include "AttackedState.h"

PlayerState* ShotWeaponState::update(ModulePlayer& player)
{
	if (event == PLAYER_HIT_BACK) return new AttackedState(ATTACKED_FROM_BEHIND);
	else if (event == PLAYER_HIT_FRONT) return new AttackedState(ATTACKED_FROM_FRONT);

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

void ShotWeaponState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	PlayerState::OnCollision(my_collider, other_collider);
}