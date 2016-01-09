#include "AttackState.h"
#include "DecideActionState.h"
#include "Timer.h"
#include "DinoDefeatedState.h"
#include "SuperHitState.h"

DinoState* AttackState::update(ModuleDino& dino)
{
	if (event == DINO_IS_DEFEATED) return new DinoDefeatedState();
	else if (event == DINO_GET_SUPERHIT) return new SuperHitState();
	else if (event == DINO_GET_HIT) dino.CloseEye(1000);

	switch (substate)
	{
	case PRE_DINO_OPENING_MOUTH:
		dino.SetCurrentAnimation(&dino.openmouth);
		substate = DINO_OPENING_MOUTH;
		break;
	case DINO_OPENING_MOUTH:
		if (dino.current_animation->Finished())
		{
			timer = new Timer(OPEN_MOUTH_TIME);
			timer->StartTimer();
			substate = DINO_MOUTH_OPEN;
		}
		break;
	case DINO_MOUTH_OPEN:
		if (projectile != FAKE_ATTACK && timer->ElapsedTime() >= OPEN_MOUTH_TIME / 2) substate = PRE_DINO_SHOT;
		
		if (timer->TimeOver()) substate = PRE_DINO_CLOSING_MOUTH;
		break;
	case PRE_DINO_SHOT:
		Shot(&dino, projectile);
		substate = DINO_SHOT;
		break;
	case DINO_SHOT:
		if (timer->TimeOver()) substate = PRE_DINO_CLOSING_MOUTH;
		break;
	case PRE_DINO_CLOSING_MOUTH:
		dino.SetCurrentAnimation(&dino.closemouth);
		substate = DINO_CLOSING_MOUTH;
		break;
	case DINO_CLOSING_MOUTH:
		if (dino.current_animation->Finished())
		{
			dino.player_too_near = false;
			return new DecideActionState();
		}
	}
	
	return SAME_STATE;
}

AttackState::~AttackState()
{
	delete timer;
}

void AttackState::enter(ModuleDino& dino)
{
	substate = PRE_DINO_OPENING_MOUTH;
}

void AttackState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	DinoState::OnCollision(my_collider, other_collider);
}
