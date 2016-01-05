#ifndef __PARTICLEENEMY_H__
#define __PARTICLEENEMY_H__

#include "Particle.h"

class Animation;

enum enemy_state
{
	ENEMY_BOUNCING,
	ENEMY_HIT
};

class ParticleEnemy : public Particle
{
public:
	ParticleEnemy(particle_type type, Sprite* generator);
	~ParticleEnemy();

	void ParticleUpdate();
	void OnCollision(Collider* c1, Collider* c2);

private:
	Animation* rollingenemy;
	Animation* hitenemy;
	enemy_state state;
	collider_type first_bounce;
};

#endif //__PARTICLEENEMY_H__