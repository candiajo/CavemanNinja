#ifndef __PARTICLEBONE_H__
#define __PARTICLEBONE_H__

#include "Particle.h"

class Animation;

enum bone_state
{
	BONE_WAITING_DELAY,
	BONE_FORWARD,
	BONE_FALLING,
	BONE_UP,
	BONE_LAST_MOMENT
};

class ParticleBone : public Particle
{
public:
	ParticleBone(particle_type type, Sprite* generator);
	~ParticleBone();

	void ParticleUpdate();
	void OnCollision(Collider* my_collider, Collider* other_collider);

	bone_state state;

private:
	unsigned int fx_player_attack;
	unsigned int fx_player_superattack;
	bone_state first_state;
	Timer* delay;
	Animation* bone_animation;
	float distance_straight;	// distance that the bone goes straight (then falls)
};

#endif //__PARTICLEBONE_H__