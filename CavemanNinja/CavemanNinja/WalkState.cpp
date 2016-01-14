#include "WalkState.h"
#include "IdleState.h"
#include "CrouchState.h"
#include "Collider.h"
#include "JumpState.h"
#include "ShotWeaponState.h"
#include "TiredState.h"
#include "AttackedState.h"
#include "ScaredState.h"

PlayerState* WalkState::Update(ModulePlayer& player)
{
	if (event == PLAYER_HIT_BACK) return new AttackedState(ATTACKED_FROM_BEHIND);
	else if (event == PLAYER_HIT_FRONT) return new AttackedState(ATTACKED_FROM_FRONT);
	else if (event == ENTER_DINO) return new ScaredState();

	CheckPosition(player);

	if (player.is_tired)
	{
		player.x_speed = 0;
		return new TiredState();
	}

	if (event == WALK_OFF_PLATFORM)
	{
		return new JumpState(FALLING);
	}

	if (App->input->GetKey(FIRE_BUTTON) == KEY_UP && player.rolling_arm)
	{
		if (player.charge_enough)
			return new ShotWeaponState(SUPER);
		else
			player.SetCurrentAnimation(player.current_animation);
	}

	if (App->input->GetKey(LEFT_BUTTON) == KEY_UP ||
		App->input->GetKey(RIGHT_BUTTON) == KEY_UP)
	{
		return new IdleState();
	}
	else if (App->input->GetKey(DOWN_BUTTON) == KEY_DOWN)
	{
		return new CrouchState();
	}
	else if (App->input->GetKey(JUMP_BUTTON) == KEY_DOWN)
	{
		if (App->input->GetKey(UP_BUTTON) == KEY_REPEAT)
			return new JumpState(SUPERJUMP);
		else
			return new JumpState(NORMALJUMP);
	}
	else if (App->input->GetKey(FIRE_BUTTON) == KEY_DOWN)
	{
		return new ShotWeaponState(HORIZONTAL);
	}
	else if (App->input->GetKey(FIRE_BUTTON) == KEY_UP)
	{
		player.SetCurrentAnimation(&player.walk);
	}
	else
	{
		if (player.direction == LEFT) player.x_speed = -DEFAULT_X_SPEED;
		else if (player.direction == RIGHT)	player.x_speed = DEFAULT_X_SPEED;
	}
	return SAME_STATE;
}

void WalkState::Enter(ModulePlayer& player)
{
	if (App->input->GetKey(LEFT_BUTTON) == KEY_REPEAT)
		player.direction = LEFT;
	else if (App->input->GetKey(RIGHT_BUTTON) == KEY_REPEAT)
		player.direction = RIGHT;

	if (App->input->GetKey(FIRE_BUTTON) == KEY_REPEAT)
	{
		player.SetCurrentAnimation(&player.walk, ANGRY_VERSION);
		RollArm(&player);
	}
	else player.SetCurrentAnimation(&player.walk);
}

void WalkState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	PlayerState::OnCollision(my_collider, other_collider);

	ModulePlayer* player = dynamic_cast<ModulePlayer*>(my_collider->callback);

	if (my_collider->type == COLLIDER_DETECT_GROUND &&
		other_collider->type == COLLIDER_GROUND || other_collider->type == COLLIDER_PLATFORM)
	{
		while (my_collider->IsColliding(other_collider))
		{
			player->position.y -= 1;
			dynamic_cast<Sprite*>(player)->PlaceColliders();
		}
	}
}



