#ifndef __PARTICLEDINOTAIL_H__
#define __PARTICLEDINOTAIL_H__

#include "Particle.h"

#define TAIL_SPEED_FORWARD 3.5
#define TAIL_SPEED_BACKWARDS 2
#define TAIL_LIMIT_RIGHT 0
#define TAIL_LIMIT_LEFT -136
#define TAIL_Y 165

class Animation;

enum dinotail_state
{
	TAIL_FORWARD,
	TAIL_BACKWARDS,
	TAIL_STOP
};

class ParticleDinoTail : public Particle
{
public:
	ParticleDinoTail(particle_type type, Sprite* generator);
	~ParticleDinoTail();

	void ParticleUpdate();
	void OnCollision(Collider* c1, Collider* c2);

private:
	Animation* dinotail;
	dinotail_state state;
};

#endif //__PARTICLEDINOTAIL_H__