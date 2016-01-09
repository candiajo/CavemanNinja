#ifndef __DINOSTATE_H__
#define __DINOSTATE_H__

#define VERY_FAR_POSITION -20	// dino at the left of the screen
#define FAR_POSITION -2			// dino far from player
#define MIDDLE_POSITION 30		// dino at middle distance
#define NEAR_POSITION 68		// dino near player
#define ATTACK_SPEED 3
#define MOVE_SPEED 1.5
#define OPEN_MOUTH_TIME 800

#include "ModuleDino.h"
#include "ModuleInput.h"
#include "Application.h"
#include "ModuleParticles.h"

enum dino_substate
{
	DINO_MOVING_BACK,
	DINO_MOVING_FORWARD,
	DINO_STOP,
	PRE_DINO_BITE,
	DINO_BITE,
	PRE_DINO_CLOSING_MOUTH,
	DINO_CLOSING_MOUTH,
	PRE_DINO_OPENING_MOUTH,
	DINO_OPENING_MOUTH,
	DINO_MOUTH_OPEN,
	PRE_DINO_SHOT,
	DINO_SHOT,
	DINO_DEFEATED_HIT,
	DINO_DEFEATED_BACKWARDS,
	DINO_DEFEATED_FALLING,
	DINO_DEFEATED_BOUNCE,
	DINO_DEFEATED_FINAL
};

class DinoState
{
public:
	virtual ~DinoState() {};
	virtual DinoState* update(ModuleDino& dino) = 0;
	virtual void enter(ModuleDino& dino) = 0;
	virtual void OnCollision(Collider* my_collider, Collider* other_collider);

protected:
	game_events event = NO_EVENT;
	dino_substate substate;

	void Shot(ModuleDino* dino, particle_type projectile);
	float Y_variation();

	float total_y_variation = 0.0f;
	float y_variation = 0.1f;
	float y_original;
};

#endif //__DINOSTATE_H__