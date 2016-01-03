#include "ShotcrouchState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "CrouchState.h"
#include "ModuleParticles.h"


#include "SDL.h"

ShotcrouchState::ShotcrouchState()
{}

PlayerState* ShotcrouchState::update(ModulePlayer& player)
{
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

void ShotcrouchState::enter(ModulePlayer& player)
{
	player.x_speed = 0;
	player.SetCurrentAnimation(&player.shotcrouch);
	Shot(&player, AXE_CROUCH);
}