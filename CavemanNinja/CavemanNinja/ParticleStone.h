#ifndef __PARTICLESTONE_H__
#define __PARTICLESTONE_H__

#include "Particle.h"

class Animation;

enum stone_state
{
	STONE_ROLLING,
	STONE_BOUNCING,
	STONE_BREAKING
};

class ParticleStone : public Particle
{
public:
	ParticleStone(particle_type type, Sprite* generator);
	~ParticleStone();

	void ParticleUpdate();
	void OnCollision(Collider* my_collider, Collider* other_collider);

private:
	Animation* rollingstone_animation;
	Animation* breakingstone_animation;
	stone_state state;
	collider_type first_bounce;
	unsigned int fx_weapon_hit;
};

#endif //__PARTICLESTONE_H_