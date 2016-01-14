#include "IdleState.h"
#include "ScaredState.h"
#include "Timer.h"
#include "ModuleSceneDino.h"

ScaredState::~ScaredState()
{
	RELEASE(timer);
}

PlayerState* ScaredState::Update(ModulePlayer& player)
{
	if (timer->TimeOver()) return new IdleState();
	else return SAME_STATE;
}

void ScaredState::Enter(ModulePlayer& player)
{
	App->scene_dino->enter_dino = false;

	player.x_speed = 0;
	player.y_speed = 0;
	player.direction = LEFT;

	if (player.rolling_arm) player.StopArm();

	player.SetCurrentAnimation(&player.scared);

	timer = new Timer(1000);
	timer->StartTimer();
}
