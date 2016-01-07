#include "TiredState.h"
#include "Timer.h"
#include "IdleState.h"
#include "CrouchState.h"
#include "WalkState.h"
#include "JumpState.h"
#include "LookupState.h"
#include "ShotWeaponState.h"
#include "AttackedState.h"

#include "SDL.h"

IdleState::IdleState() : PlayerState()
{}

IdleState::~IdleState()
{
	delete timer;
}

PlayerState* IdleState::update(ModulePlayer& player)
{
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

	if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_UP && player.rolling_arm)
	{
		if (player.charge_enough)
			return new ShotWeaponState(SUPER_AXE);
		else
			player.SetCurrentAnimation(&player.idle);
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		return new CrouchState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT ||
		     App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		return new WalkState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_DOWN &&
		     App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		return new JumpState(SUPERJUMP);
	}
	else if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_DOWN)
	{
		return new JumpState(NORMALJUMP);
	}
	else if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		return new LookupState();
	}
	else if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_DOWN)
	{
		return new ShotWeaponState();
	}

	return SAME_STATE;
}

void IdleState::enter(ModulePlayer& player)
{
	player.x_speed = 0;
	player.y_speed = 0;
	if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT)
	{
		player.SetCurrentAnimation(&player.idle, ANGRY_VERSION);
		RollArm(&player);
	}
	else player.SetCurrentAnimation(&player.idle);

	timer = new Timer(3000);
	timer->StartTimer();
}