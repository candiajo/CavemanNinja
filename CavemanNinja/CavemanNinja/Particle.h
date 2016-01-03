#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Sprite.h"

class Particle : public Sprite
{
public:
	Particle();
	Particle(particle_type type, Sprite* generator);
	~Particle();

	virtual void ParticleUpdate() = 0;

	bool to_destroy = false;
	Point offset;

protected:
	particle_type type;
};

#endif //__PARTICLE_H__
