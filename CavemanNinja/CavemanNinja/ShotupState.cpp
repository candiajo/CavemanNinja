#include "ShotupState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "LookUpState.h"
#include "ModuleParticles.h"
#include "AttackedState.h"

ShotupState::ShotupState()
{}

PlayerState* ShotupState::update(ModulePlayer& player)
{
	if (event == PLAYER_HIT_BACK) return new AttackedState(ATTACKED_FROM_BEHIND);
	else if (event == PLAYER_HIT_FRONT) return new AttackedState(ATTACKED_FROM_FRONT);

	if (player.current_animation->Finished())
	{
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			return new LookUpState();
		else
			return new IdleState();
	}
	else
	{
		return nullptr;
	}
}

void ShotupState::enter(ModulePlayer& player)
{
	player.x_speed = 0;
	player.SetCurrentAnimation(&player.shotup);
	Shot(&player, AXE_VERT);
}

void ShotupState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	PlayerState::OnCollision(my_collider, other_collider);
}