#include "MoveState.h"
#include "DecideActionState.h"
#include "AttackState.h"
#include "DinoDefeatedState.h"
#include "SuperHitState.h"
#include "ModuleAudio.h"

MoveState::MoveState(int final_position, particle_type projectile) : 
final_position(final_position), 
projectile(projectile)
{}

DinoState* MoveState::update(ModuleDino& dino)
{
	if (event == DINO_IS_DEFEATED) return new DinoDefeatedState();
	else if (event == DINO_GET_SUPERHIT) return new SuperHitState();
	else if (event == DINO_GET_HIT) dino.CloseEye(1000);

	switch (substate)
	{
	case DINO_MOVING_BACK:
		dino.position.x -= MOVE_SPEED;
		dino.position.y += Y_variation();

		if (dino.position.x <= final_position)
		{
			App->audio->StopFxChannel(channel);
			dino.position.x = (float)final_position;	// to ensure that it's placed in the exact pixel
			substate = DINO_STOP;
		}
		break;
	case DINO_MOVING_FORWARD:
		dino.position.x += MOVE_SPEED;

		dino.position.y += Y_variation();

		if (dino.position.x >= final_position)
		{
			App->audio->StopFxChannel(channel);
			dino.SetCurrentAnimation(&dino.semiclosemouth);
			dino.position.x = (float)final_position;	// to ensure that it's placed in the exact pixel
			substate = DINO_CLOSING_MOUTH;
		}
		break;
	case DINO_CLOSING_MOUTH:
		if (dino.current_animation->Finished())
			substate = DINO_STOP;
		break;
	case DINO_STOP:
		dino.dinobody.speed = 0.0f;
		dino.dinobody.Reset();
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
		channel = App->audio->PlayFx(dino.fx_dino_stomps, NO_REPEAT);

	}
	else if (dino.position.x < final_position)				// dino is going forward
	{
		substate = DINO_MOVING_FORWARD;
		dino.SetCurrentAnimation(&dino.semiopenmouth);
		dino.semiopenmouth.SetLastFrame();					// set dino semi open mouth frame (last frame of the animation)
		channel = App->audio->PlayFx(dino.fx_dino_stomps, NO_REPEAT);
	}
	else
	{
		substate = DINO_STOP;
	}

	if (projectile == DINO_TAIL)
	{
		dino.dinobody.speed = 0.15f;
	}

	y_original = dino.position.y;
}

void MoveState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	DinoState::OnCollision(my_collider, other_collider);
}
