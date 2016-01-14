#ifndef __PARTICLEHIT_H__
#define __PARTICLEHIT_H__

#include "Particle.h"

class Animation;

class ParticleHit : public Particle
{
public:
	ParticleHit(particle_type type, Sprite* generator);
	~ParticleHit();

	void ParticleUpdate();
	void OnCollision(Collider* my_collider, Collider* other_collider) {};

private:
	Timer* delay;
	Animation* hit_animation;
};

#endif //__PARTICLEHIT_H__