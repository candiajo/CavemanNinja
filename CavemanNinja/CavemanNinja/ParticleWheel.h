#ifndef __PARTICLEWHEEL_H__
#define __PARTICLEWHEEL_H__

#include "Particle.h"

class Animation;

enum wheel_state
{
	WHEEL_WAITING_DELAY,
	WHEEL_FLY_FORWARD,
	WHEEL_ROLLING,
	WHEEL_FALLING,
	WHEEL_UP,
	WHEEL_DOWN,
	WHEEL_LAST_MOMENT
};

class ParticleWheel : public Particle
{
public:
	ParticleWheel(particle_type type, Sprite* generator);
	~ParticleWheel();

	void ParticleUpdate();
	void OnCollision(Collider* my_collider, Collider* other_collider);

	wheel_state state;

private:
	unsigned int fx_player_attack;
	unsigned int fx_player_superattack;
	wheel_state first_state;
	Timer* delay;
	Animation* wheel_animation;
	float distance_straight;	// distance that the wheel goes straight (then falls)
	int hits;
};

#endif //__PARTICLEWHEEL_H__