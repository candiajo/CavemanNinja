#include "LookUpState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "ShotupState.h"
#include "WalkState.h"
#include "TiredState.h"
#include "ShotWeaponState.h"
#include "AttackedState.h"

LookUpState::LookUpState()
{}

PlayerState* LookUpState::Update(ModulePlayer& player)
{
	if (event == PLAYER_HIT_BACK) return new AttackedState(ATTACKED_FROM_BEHIND);
	else if (event == PLAYER_HIT_FRONT) return new AttackedState(ATTACKED_FROM_FRONT);

	CheckPosition(player);

	if (player.is_tired) return new TiredState();

	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_UP && player.rolling_arm)
	{
		if (player.charge_enough)
			return new ShotWeaponState(SUPER_AXE);
		else
			player.SetCurrentAnimation(player.current_animation);
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
	{
		return new IdleState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
	{
		return new JumpState(SUPERJUMP);
	}
	else if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		return new ShotupState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT ||
		App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		return new WalkState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_UP)
	{
		player.SetCurrentAnimation(&player.lookup);
	}
		return SAME_STATE;
}

void LookUpState::Enter(ModulePlayer& player)
{
	player.x_speed = 0;
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_REPEAT)
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