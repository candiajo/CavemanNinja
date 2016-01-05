#ifndef __MODULEDINOSTATE_H__
#define __MODULEDINOSTATE_H__

#define FAR_POSITION -2		// dino far from player
#define MIDDLE_POSITION 30	// dino at middle distance
#define NEAR_POSITION 68	// dino near player
#define ATTACK_SPEED 4
#define MOVE_SPEED 2.5
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
	DINO_SHOT
};

class DinoState
{
public:
	virtual ~DinoState() {};
	virtual DinoState* update(ModuleDino& dino) = 0;
	virtual void enter(ModuleDino& dino) = 0;
	virtual void OnCollision(Collider* c1, Collider* c2) {};

protected:
	game_events event;
	dino_substate substate;

	void Shot(ModuleDino* dino, particle_type projectile)
	{
		App->particles->AddParticle(projectile, dynamic_cast<Module*>(dino));
	}

	float Y_variation()
	{
		if (abs(total_y_variation) >= 0.5f) y_variation *= -1.0f;
		total_y_variation += y_variation;
		return total_y_variation;
	}

	float total_y_variation = 0.0f;
	float y_variation = 0.1f;
	float y_original;
};

#endif //__MODULEDINOSTATE_H__