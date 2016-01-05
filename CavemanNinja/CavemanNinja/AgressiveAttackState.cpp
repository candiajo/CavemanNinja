#include "AgressiveAttackState.h"
#include "MoveState.h"

#include "SDL.h"

DinoState* AgressiveAttackState::update(ModuleDino& dino)
{
	switch (substate)
	{
	case DINO_MOVING_FORWARD:
		dino.position.x += ATTACK_SPEED;
		dino.position.y += Y_variation();
		if (dino.position.x >= NEAR_POSITION) substate = PRE_DINO_BITE;
		break;

	case PRE_DINO_BITE:
		dino.x_speed = 0;
		dino.position.y += Y_variation();
		dino.SetCurrentAnimation(&dino.closemouth);
		substate = DINO_BITE;
		break;

	case DINO_BITE:
		if (dino.current_animation->Finished()) return new MoveState(FAR_POSITION);
		break;
	}
	
	return SAME_STATE;
}

void AgressiveAttackState::enter(ModuleDino& dino)
{
	dino.SetCurrentAnimation(&dino.openmouth);
	dino.openmouth.SetLastFrame();	// set dino open mouth (last frame of the animation)
	substate = DINO_MOVING_FORWARD;
	y_original = dino.position.y;
}