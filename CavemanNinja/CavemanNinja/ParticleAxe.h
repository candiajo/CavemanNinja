#ifndef __PARTICLEAXE_H__
#define __PARTICLEAXE_H__

#include "Particle.h"

class Animation;

enum axe_state
{
	AXE_FORWARD,
	AXE_FALLING_FORWARD,
	AXE_UP,
	AXE_FALLING_DOWN,
	AXE_ON_GROUND
};

class ParticleAxe : public Particle
{
public:
	ParticleAxe(particle_type type, Sprite* generator);
	~ParticleAxe();
	
	void ParticleUpdate();
	void OnCollision(Collider* c1, Collider* c2);

private:
	Animation* axe;
	axe_state state;
	int distance_straight = 0;	// distance that the axe goes straight (then falls)
};

#endif //__PARTICLEAXE_H_