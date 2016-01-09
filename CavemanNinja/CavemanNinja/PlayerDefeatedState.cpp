#include "PlayerDefeatedState.h"
#include "IdleState.h"
#include "ModuleBeginLevel.h"
#include "ModuleSceneTitle.h"
#include "ModuleSceneDino.h"
#include "Timer.h"

PlayerDefeatedState::~PlayerDefeatedState()
{
	RELEASE(timer);
}

PlayerState* PlayerDefeatedState::update(ModulePlayer& player)
{
	if (timer->TimeOver()) App->scene_dino->player_defeated = true;
	return nullptr;
}

void PlayerDefeatedState::enter(ModulePlayer& player)
{
	timer = new Timer(1500);
	timer->StartTimer();

	if (attacked_from == ATTACKED_FROM_BEHIND) player.SetCurrentAnimation(&player.backdying);
	else player.SetCurrentAnimation(&player.frontdying);
}
