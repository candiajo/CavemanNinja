#include "ShotcrouchState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "CrouchState.h"
#include "ModuleParticles.h"
#include "AttackedState.h"

ShotcrouchState::ShotcrouchState()
{}

PlayerState* ShotcrouchState::Update(ModulePlayer& player)
{
	if (event == PLAYER_HIT_BACK) return new AttackedState(ATTACKED_FROM_BEHIND);
	else if (event == PLAYER_HIT_FRONT) return new AttackedState(ATTACKED_FROM_FRONT);

	if (player.current_animation->Finished())
	{
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			return new CrouchState();
		else
			return new IdleState();
	}
	else
	{
		return nullptr;
	}
}

void ShotcrouchState::Enter(ModulePlayer& player)
{
	player.x_speed = 0;
	player.SetCurrentAnimation(&player.shotcrouch);
	ThrowParticle(&player, AXE_CROUCH);
}

void ShotcrouchState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	PlayerState::OnCollision(my_collider, other_collider);
}