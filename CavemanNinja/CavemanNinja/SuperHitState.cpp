#include "ModuleAudio.h"
#include "ModuleDino.h"
#include "SuperHitState.h"
#include "Timer.h"
#include "DecideActionState.h"
#include "MoveState.h"
#include "SpriteDinoBody.h"

DinoState* SuperHitState::Update(ModuleDino& dino)
{
	if (timer->TimeOver()) return new MoveState(NEAR_POSITION, FAST_STONE);
	else return SAME_STATE;
}

SuperHitState::~SuperHitState()
{
	RELEASE(timer);
};

void SuperHitState::Enter(ModuleDino& dino)
{
	dino.SetCurrentAnimation(&dino.superhit);
	timer = new Timer(1000);
	timer->StartTimer();
	dino.dinobody_sprite->current_animation->speed = 0.2f;
	App->audio->PlayFx(App->dino->fx_dino_roar);
}