#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Sprite.h"

class Particle : public Sprite
{
public:
	Particle();
	Particle(particle_type type, Sprite* generator);
	virtual ~Particle();

	virtual void ParticleUpdate() = 0;

	bool to_destroy = false;
	Point offset;
	int damage;

protected:
	particle_type type;
	int life;

};

#endif //__PARTICLE_H__
