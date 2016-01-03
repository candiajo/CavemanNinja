#ifndef __PARTICLESTONE_H__
#define __PARTICLESTONE_H__

#include "Particle.h"

class Animation;

enum stone_state
{
	STONE_ROLLING,
	STONE_BOUNCING
};

class ParticleStone : public Particle
{
public:
	ParticleStone(particle_type type, Sprite* generator);
	~ParticleStone();

	void ParticleUpdate();
	void OnCollision(Collider* c1, Collider* c2);

private:
	Animation* rollingstone;
	Animation* breakingstone;
	stone_state state;
};

#endif //__PARTICLESTONE_H_