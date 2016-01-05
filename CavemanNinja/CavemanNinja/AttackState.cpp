#include "AttackState.h"
#include "DecideActionState.h"
#include "Timer.h"

DinoState* AttackState::update(ModuleDino& dino)
{
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
		if (dino.current_animation->Finished())	return new DecideActionState();
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