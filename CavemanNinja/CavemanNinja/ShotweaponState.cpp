#include "ShotWeaponState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "ModuleParticles.h"
#include "AttackedState.h"
#include "ScaredState.h"

PlayerState* ShotWeaponState::Update(ModulePlayer& player)
{
	if (event == PLAYER_HIT_BACK) return new AttackedState(ATTACKED_FROM_BEHIND);
	else if (event == PLAYER_HIT_FRONT) return new AttackedState(ATTACKED_FROM_FRONT);
	else if (event == ENTER_DINO) return new ScaredState();

	CheckPosition(player);

	if (player.current_animation->Finished())
	{
		return new IdleState();
	}
	else
	{
		return SAME_STATE;
	}
}

void ShotWeaponState::Enter(ModulePlayer& player)
{
	player.x_speed = 0;

	if (weapon_subtype == SUPER)
	{
		player.SetCurrentAnimation(&player.supershot);
		ThrowParticle(&player, player.GetCurrentWeapon(weapon_subtype));
	}
	else if (player.weapons_on_screen < 2)
	{
		player.SetCurrentAnimation(&player.shotweapon);
		ThrowParticle(&player, player.GetCurrentWeapon(weapon_subtype));
	}
	else
	{
		player.SetCurrentAnimation(&player.shotnoweapon);
	}
}

void ShotWeaponState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	PlayerState::OnCollision(my_collider, other_collider);
}