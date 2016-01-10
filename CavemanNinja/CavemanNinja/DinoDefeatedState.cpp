#include "ModuleAudio.h"
#include "ModuleSceneDino.h"
#include "ModuleDino.h"
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
		dino.position.x -= 0.8f;
		dino.position.y += Y_variation();
		if (dino.position.x <= DINO_LEFT_LIMIT)
		{
			dino.spritedinobody->SetCurrentAnimation(dino.spritedinobody->dinobodyground_animation);
			substate = DINO_DEFEATED_FALLING;
		}
		break;
	case DINO_DEFEATED_FALLING:
		dino.position.x += 0.4f;
		//dino.position.y *= 1.04f;
		dino.y_speed += 0.1f;
		dino.position.y += dino.y_speed;

		if (dino.position.y >= DINO_DOWN_LIMIT) 
		{ 
			substate = DINO_DEFEATED_BOUNCE;  
			dino.y_speed = -2.0f;
			dino.position.y = DINO_DOWN_LIMIT - 1; 
		}
		break;
	case DINO_DEFEATED_BOUNCE:
		dino.y_speed += 0.1f;
		dino.position.y += dino.y_speed;
		if (dino.position.y >= DINO_DOWN_LIMIT)	substate = DINO_STOP;
	case DINO_STOP:
		App->scene_dino->dino_defeated = true;
	}
	return nullptr;
}

void DinoDefeatedState::enter(ModuleDino& dino)
{
	dino.SetCurrentAnimation(&dino.superhit);
	timer = new Timer(1000);
	timer->StartTimer();
	dino.spritedinobody->current_animation->speed = 0.2f;
	substate = DINO_DEFEATED_HIT;
	App->audio->PlayFx(App->dino->fx_dino_defeated);
}