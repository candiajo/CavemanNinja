#include "ShotcrouchState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "CrouchState.h"
#include "ModuleParticles.h"
#include "AttackedState.h"
#include "ScaredState.h"

PlayerState* ShotcrouchState::Update(ModulePlayer& player)
{
	if (event == PLAYER_HIT_BACK) return new AttackedState(ATTACKED_FROM_BEHIND);
	else if (event == PLAYER_HIT_FRONT) return new AttackedState(ATTACKED_FROM_FRONT);
	else if (event == ENTER_DINO) return new ScaredState();

	CheckPosition(player);

	if (player.current_animation->Finished())
	{
		if (App->input->GetKey(DOWN_BUTTON) == KEY_REPEAT)
			return new CrouchState();
		else
			return new IdleState();
	}
	else
	{
		return SAME_STATE;
	}
}

void ShotcrouchState::Enter(ModulePlayer& player)
{
	player.x_speed = 0;
	player.SetCurrentAnimation(&player.shotcrouch);
	ThrowParticle(&player, player.GetCurrentWeapon(CROUCH));
}

void ShotcrouchState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	PlayerState::OnCollision(my_collider, other_collider);
}