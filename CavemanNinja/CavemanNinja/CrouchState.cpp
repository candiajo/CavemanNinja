#include "CrouchState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "ShotcrouchState.h"
#include "TiredState.h"
#include "ShotWeaponState.h"
#include "AttackedState.h"
#include "ScaredState.h"

PlayerState* CrouchState::Update(ModulePlayer& player)
{
	if (event == PLAYER_HIT_BACK) return new AttackedState(ATTACKED_FROM_BEHIND);
	else if (event == PLAYER_HIT_FRONT) return new AttackedState(ATTACKED_FROM_FRONT);
	else if (event == ENTER_DINO) return new ScaredState();

	CheckPosition(player);

	player.is_crouch = false; // will be true if don't change state

	if (player.is_tired)
	{
		player.is_crouch = false;
		return new TiredState();
	}

	if (App->input->GetKey(FIRE_BUTTON) == KEY_UP && player.rolling_arm)
	{
		if (player.charge_enough)
			return new ShotWeaponState(SUPER);
		else
			player.SetCurrentAnimation(player.current_animation);
	}

	if (App->input->GetKey(DOWN_BUTTON) == KEY_UP)
	{
		return new IdleState();
	}
	else if (App->input->GetKey(JUMP_BUTTON) == KEY_DOWN &&
		     player.position.y < 150)	// for avoiding downjump from the ground
	{
		return new JumpState(DOWNJUMP);
	}
	else if (App->input->GetKey(FIRE_BUTTON) == KEY_DOWN)
	{
		return new ShotcrouchState();
	}
	else if (App->input->GetKey(FIRE_BUTTON) == KEY_UP)
	{
		player.SetCurrentAnimation(&player.crouch);
	}

	player.is_crouch = true;

	return SAME_STATE;

}

void CrouchState::Enter(ModulePlayer& player)
{
	player.is_crouch = true;
	player.x_speed = 0;
	if (App->input->GetKey(FIRE_BUTTON) == KEY_REPEAT)
	{
		RollArm(&player);
		player.SetCurrentAnimation(&player.crouch, ANGRY_VERSION);
	}
	else
		player.SetCurrentAnimation(&player.crouch);
}

void CrouchState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	PlayerState::OnCollision(my_collider, other_collider);
}