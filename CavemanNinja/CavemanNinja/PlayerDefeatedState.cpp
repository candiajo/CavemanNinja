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
	if (timer->TimeOver()) App->player1->player_end = true;
	return SAME_STATE;
}

void PlayerDefeatedState::enter(ModulePlayer& player)
{
	timer = new Timer(1500);
	timer->StartTimer();

	if (attacked_from == ATTACKED_FROM_BEHIND) player.SetCurrentAnimation(&player.backdying);
	else player.SetCurrentAnimation(&player.frontdying);

	player.is_defeated = true;
}
