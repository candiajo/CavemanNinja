#include "LookUpState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "ShotupState.h"
#include "WalkState.h"
#include "TiredState.h"
#include "ShotWeaponState.h"
#include "AttackedState.h"
#include "ScaredState.h"

PlayerState* LookUpState::Update(ModulePlayer& player)
{
	if (event == PLAYER_HIT_BACK) return new AttackedState(ATTACKED_FROM_BEHIND);
	else if (event == PLAYER_HIT_FRONT) return new AttackedState(ATTACKED_FROM_FRONT);
	else if (event == ENTER_DINO) return new ScaredState();

	CheckPosition(player);

	if (player.is_tired) return new TiredState();

	if (App->input->GetKey(FIRE_BUTTON) == KEY_UP && player.rolling_arm)
	{
		if (player.charge_enough)
			return new ShotWeaponState(SUPER);
		else
			player.SetCurrentAnimation(player.current_animation);
	}

	if (App->input->GetKey(UP_BUTTON) == KEY_UP)
	{
		return new IdleState();
	}
	else if (App->input->GetKey(JUMP_BUTTON) == KEY_DOWN)
	{
		return new JumpState(SUPERJUMP);
	}
	else if (App->input->GetKey(FIRE_BUTTON) == KEY_DOWN)
	{
		return new ShotupState();
	}
	else if (App->input->GetKey(LEFT_BUTTON) == KEY_REPEAT ||
		App->input->GetKey(RIGHT_BUTTON) == KEY_REPEAT)
	{
		return new WalkState();
	}
	else if (App->input->GetKey(FIRE_BUTTON) == KEY_UP)
	{
		player.SetCurrentAnimation(&player.lookup);
	}
		return SAME_STATE;
}

void LookUpState::Enter(ModulePlayer& player)
{
	player.x_speed = 0;
	if (App->input->GetKey(FIRE_BUTTON) == KEY_REPEAT)
	{
		RollArm(&player);
		player.SetCurrentAnimation(&player.lookup, ANGRY_VERSION);
	}
	else
		player.SetCurrentAnimation(&player.lookup);
}

void LookUpState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	PlayerState::OnCollision(my_collider, other_collider);
}