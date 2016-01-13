#include "ShotupState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "LookUpState.h"
#include "ModuleParticles.h"
#include "AttackedState.h"

PlayerState* ShotupState::Update(ModulePlayer& player)
{
	if (event == PLAYER_HIT_BACK) return new AttackedState(ATTACKED_FROM_BEHIND);
	else if (event == PLAYER_HIT_FRONT) return new AttackedState(ATTACKED_FROM_FRONT);

	if (player.current_animation->Finished())
	{
		if (App->input->GetKey(UP_BUTTON) == KEY_REPEAT)
			return new LookUpState();
		else
			return new IdleState();
	}
	else
	{
		return SAME_STATE;
	}
}

void ShotupState::Enter(ModulePlayer& player)
{
	player.x_speed = 0;
	if (player.weapons_on_screen < 2)
	{
		player.SetCurrentAnimation(&player.shotup);
		ThrowParticle(&player, player.GetCurrentWeapon(VERTICAL));
	}
	else
	{
		player.SetCurrentAnimation(&player.shotupnw);
	}
}

void ShotupState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	PlayerState::OnCollision(my_collider, other_collider);
}