#include "MoveState.h"
#include "DecideActionState.h"
#include "AttackState.h"

MoveState::MoveState(int final_position, particle_type projectile) : 
final_position(final_position), 
projectile(projectile)
{}

DinoState* MoveState::update(ModuleDino& dino)
{
	switch (substate)
	{
	case DINO_MOVING_BACK:
		dino.position.x -= MOVE_SPEED;
		dino.position.y += Y_variation();

		if (dino.position.x <= final_position)
		{
			dino.position.x = final_position;	// to ensure that it's placed in the exact pixel
			substate = DINO_STOP;
		}
		break;
	case DINO_MOVING_FORWARD:
		dino.position.x += MOVE_SPEED;

		dino.position.y += Y_variation();

		if (dino.position.x >= final_position)
		{
			dino.SetCurrentAnimation(&dino.semiclosemouth);
			dino.position.x = final_position;	// to ensure that it's placed in the exact pixel
			substate = DINO_CLOSING_MOUTH;
		}
		break;
	case DINO_CLOSING_MOUTH:
		if (dino.current_animation->Finished())
			substate = DINO_STOP;
		break;
	case DINO_STOP:
		dino.position.y = y_original;
		if (projectile != NO_PARTICLE) return new AttackState(projectile);
		else return new DecideActionState();
		break;
	}

	return SAME_STATE;						// still moving to final position
}

void MoveState::enter(ModuleDino& dino)
{
	if (dino.position.x > final_position)					// dino is going back
	{
		substate = DINO_MOVING_BACK;
		dino.SetCurrentAnimation(&dino.closemouth);
		dino.closemouth.SetLastFrame();						// set closed mouth frame
	}
	else if (dino.position.x < final_position)				// dino is going forward
	{
		substate = DINO_MOVING_FORWARD;
		dino.SetCurrentAnimation(&dino.semiopenmouth);
		dino.semiopenmouth.SetLastFrame();					// set dino semi open mouth frame (last frame of the animation)
	}
	else
	{
		substate = DINO_STOP;
	}

	y_original = dino.position.y;
}