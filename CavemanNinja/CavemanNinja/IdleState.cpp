#include "ModuleCollisions.h"
#include "Application.h"
#include "TiredState.h"
#include "Timer.h"
#include "IdleState.h"
#include "CrouchState.h"
#include "WalkState.h"
#include "JumpState.h"
#include "LookUpState.h"
#include "ShotWeaponState.h"
#include "AttackedState.h"
#include "Globals.h"

IdleState::~IdleState()
{
	RELEASE(timer);
}

PlayerState* IdleState::Update(ModulePlayer& player)
{
	if (event == PLAYER_HIT_BACK) return new AttackedState(ATTACKED_FROM_BEHIND);
	else if (event == PLAYER_HIT_FRONT) return new AttackedState(ATTACKED_FROM_FRONT);

	CheckPosition(player);

	if (player.is_tired) return new TiredState();

	if (player.rolling_arm) timer->StartTimer();

	if (timer->TimeOver())
	{
		if (player.current_animation == &player.salute)
			player.SetCurrentAnimation(&player.idle);
		else
			player.SetCurrentAnimation(&player.salute);

		timer->StartTimer(3000);
	}

	if (App->input->GetKey(FIRE_BUTTON) == KEY_UP && player.rolling_arm)
	{
		if (player.charge_enough)
			return new ShotWeaponState(SUPER);
		else
			player.SetCurrentAnimation(player.current_animation);
	}

	if (App->input->GetKey(DOWN_BUTTON) == KEY_REPEAT)
	{
		return new CrouchState();
	}
	else if (App->input->GetKey(LEFT_BUTTON) == KEY_REPEAT ||
		     App->input->GetKey(RIGHT_BUTTON) == KEY_REPEAT)
	{
		return new WalkState();
	}
	else if (App->input->GetKey(JUMP_BUTTON) == KEY_DOWN &&
		     App->input->GetKey(UP_BUTTON) == KEY_REPEAT)
	{
		return new JumpState(SUPERJUMP);
	}
	else if (App->input->GetKey(JUMP_BUTTON) == KEY_DOWN)
	{
		return new JumpState(NORMALJUMP);
	}
	else if (App->input->GetKey(UP_BUTTON) == KEY_REPEAT)
	{
		return new LookUpState();
	}
	else if (App->input->GetKey(FIRE_BUTTON) == KEY_DOWN)
	{
		return new ShotWeaponState(HORIZONTAL);
	}

	return SAME_STATE;
}

void IdleState::Enter(ModulePlayer& player)
{
	player.x_speed = 0;
	player.y_speed = 0;
	if (App->input->GetKey(FIRE_BUTTON) == KEY_REPEAT)
	{
		player.SetCurrentAnimation(&player.idle, ANGRY_VERSION);
		RollArm(&player);
	}
	else player.SetCurrentAnimation(&player.idle);

	timer = new Timer(3000);
	timer->StartTimer();
}

void IdleState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	PlayerState::OnCollision(my_collider, other_collider);
}