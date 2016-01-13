#ifndef __PARTICLEAXE_H__
#define __PARTICLEAXE_H__

#include "Particle.h"

class Animation;

enum axe_state
{
	AXE_WAITING_DELAY,
	AXE_FORWARD,
	AXE_FALLING,
	AXE_UP,
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
	float distance_straight;	// distance that the axe goes straight (then falls)
};

#endif //__PARTICLEAXE_H_