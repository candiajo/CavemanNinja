#ifndef __PARTICLEENEMY_H__
#define __PARTICLEENEMY_H__

#include "Particle.h"

class Animation;

enum enemy_state
{
	ENEMY_BOUNCING,
	ENEMY_HIT,
	ENEMY_DEFEATED
};

class ParticleEnemy : public Particle
{
public:
	ParticleEnemy(particle_type type, Sprite* generator);
	~ParticleEnemy();

	void ParticleUpdate();
	void OnCollision(Collider* my_collider, Collider* other_collider);

private:
	Animation* rollingenemy;
	Animation* hitenemy;
	Animation* defeatedenemy;
	enemy_state state;
	collider_type first_bounce;
	int bounces = 0;
};

#endif //__PARTICLEENEMY_H__