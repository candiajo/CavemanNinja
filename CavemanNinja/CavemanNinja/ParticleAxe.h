#ifndef __PARTICLEAXE_H__
#define __PARTICLEAXE_H__

#include "Particle.h"

class Animation;

enum axe_state
{
	AXE_WAITING_DELAY,
	AXE_FORWARD,
	AXE_FALLING_FORWARD,
	AXE_UP,
	AXE_FALLING_DOWN,
	AXE_LAST_MOMENT
};

class ParticleAxe : public Particle
{
public:
	ParticleAxe(particle_type type, Sprite* generator);
	~ParticleAxe();
	
	void ParticleUpdate();
	void OnCollision(Collider* my_collider, Collider* other_collider);

	axe_state state;

private:
	unsigned int fx_player_attack;
	unsigned int fx_player_superattack;
	axe_state first_state;
	Timer* delay;
	Animation* axe;
	int distance_straight;	// distance that the axe goes straight (then falls)
	particle_type hit_particle_type;
};

#endif //__PARTICLEAXE_H_