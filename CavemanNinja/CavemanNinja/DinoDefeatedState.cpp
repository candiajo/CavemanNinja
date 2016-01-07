#include "DinoDefeatedState.h"
#include "Timer.h"
#include "SpriteDinoBody.h"

DinoDefeatedState::~DinoDefeatedState()
{
	delete timer;
}

DinoState* DinoDefeatedState::update(ModuleDino& dino)
{
	switch (substate)
	{
	case DINO_DEFEATED_HIT:
		if (timer->TimeOver())
		{
			dino.SetCurrentAnimation(&dino.defeated);
			substate = DINO_DEFEATED_BACKWARDS;
		}
		break;
	case DINO_DEFEATED_BACKWARDS:
		dino.position.x -= 0.8;
		dino.position.y += Y_variation();
		if (dino.position.x <= DINO_LEFT_LIMIT)
		{
			dino.spritedinobody->SetCurrentAnimation(dino.spritedinobody->dinobodyground_animation);
			substate = DINO_DEFEATED_FALLING;
		}
		break;
	case DINO_DEFEATED_FALLING:
		dino.position.x += 0.4f;
		dino.position.y *= 1.04f;
		if (dino.position.y >= DINO_DOWN_LIMIT) substate = DINO_DEFEATED_BOUNCE;
		break;
	case DINO_DEFEATED_BOUNCE:
		dino.position.y *= 0.985f;
		if (dino.position.y <= DINO_DOWN_LIMIT - 20) substate = DINO_DEFEATED_FINAL;
		break;
	case DINO_DEFEATED_FINAL:
		dino.position.y *= 1.015f;
		//dino.position.y += 2.0f;
		if (dino.position.y >= DINO_DOWN_LIMIT)	substate = DINO_STOP;
	}
	return nullptr;
}

void DinoDefeatedState::enter(ModuleDino& dino)
{
	dino.SetCurrentAnimation(&dino.superhit);
	timer = new Timer(1000);
	timer->StartTimer();
	dino.spritedinobody->current_animation->speed = 0.2;
	substate = DINO_DEFEATED_HIT;
}