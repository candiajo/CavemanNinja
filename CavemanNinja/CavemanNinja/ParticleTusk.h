#ifndef __PARTICLETUSK_H__
#define __PARTICLETUSK_H__

#include "Particle.h"

class Animation;

enum tusk_state
{
	TUSK_WAITING_DELAY,
	TUSK_FORWARD,
	TUSK_UP,
	TUSK_LAST_MOMENT
};

class ParticleTusk : public Particle
{
public:
	ParticleTusk(particle_type type, Sprite* generator);
	~ParticleTusk();

	void ParticleUpdate();
	void OnCollision(Collider* my_collider, Collider* other_collider);

	tusk_state state;

private:
	unsigned int fx_player_attack;
	unsigned int fx_player_superattack;
	tusk_state first_state;
	Timer* delay;
	Animation* tusk_animation;
};

#endif //__PARTICLETUSK_H__