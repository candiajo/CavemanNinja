#include "PlayerDefeatedState.h"
#include "IdleState.h" // debug
//#include "Application.h"
#include "ModuleBeginLevel.h"
#include "ModuleSceneTitle.h"
#include "ModuleSceneDino.h"

PlayerState* PlayerDefeatedState::update(ModulePlayer& player)
{
	if (player.current_animation->Finished()) App->scene_dino->player_defeated = true; // debug return new IdleState();
	return nullptr;
}

void PlayerDefeatedState::enter(ModulePlayer& player)
{
	if (attacked_from == ATTACKED_FROM_BEHIND) player.SetCurrentAnimation(&player.backdying);
	else player.SetCurrentAnimation(&player.frontdying);
}
