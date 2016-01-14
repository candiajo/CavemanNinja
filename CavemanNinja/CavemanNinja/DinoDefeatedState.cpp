#include "ModuleAudio.h"
#include "ModuleSceneDino.h"
#include "ModuleDino.h"
#include "DinoDefeatedState.h"
#include "Timer.h"
#include "SpriteDinoBody.h"

DinoDefeatedState::~DinoDefeatedState()
{
	RELEASE(timer);
}

DinoState* DinoDefeatedState::Update(ModuleDino& dino)
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
			dino.dinobody_sprite->SetCurrentAnimation(dino.dinobody_sprite->dinobodyground_animation);
			substate = DINO_DEFEATED_FALLING;
		}
		break;

	case DINO_DEFEATED_FALLING:
		dino.position.x += 0.4f;
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
		break;

	case DINO_STOP:
		App->scene_dino->dino_defeated = true;
	}
	return SAME_STATE;
}

void DinoDefeatedState::Enter(ModuleDino& dino)
{
	dino.SetCurrentAnimation(&dino.superhit);
	timer = new Timer(1000);
	timer->StartTimer();
	dino.dinobody_sprite->current_animation->speed = 0.2f;
	substate = DINO_DEFEATED_HIT;
	App->audio->PlayFx(App->dino->fx_dino_defeated);
	App->input->DeactivateInput(13000);
}