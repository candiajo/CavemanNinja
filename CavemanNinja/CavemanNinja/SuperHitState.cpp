#include "ModuleAudio.h"
#include "ModuleDino.h"
#include "SuperHitState.h"
#include "Timer.h"
#include "DecideActionState.h"
#include "MoveState.h"
#include "SpriteDinoBody.h"

DinoState* SuperHitState::update(ModuleDino& dino)
{
	if (timer->TimeOver()) return new MoveState(NEAR_POSITION, FAST_STONE);
	else return SAME_STATE;
}

SuperHitState::~SuperHitState()
{
	delete timer;
};

void SuperHitState::enter(ModuleDino& dino)
{
	dino.SetCurrentAnimation(&dino.superhit);
	timer = new Timer(1000);
	timer->StartTimer();
	dino.spritedinobody->current_animation->speed = 0.2f;
	App->audio->PlayFx(App->dino->fx_dino_roar);
}