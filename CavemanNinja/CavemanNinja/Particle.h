#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Sprite.h"

enum particle_flag
{
	NORMAL,
	INNOCUOUS
};

class Particle : public Sprite
{
public:
	Particle();
	Particle(particle_type type);
	Particle(particle_type type, Sprite* generator);
	virtual ~Particle();

	virtual void ParticleUpdate() = 0;

	bool to_destroy = false;
	Point offset;
	particle_type type;
	particle_flag particle_flag;
	weapon_subtype subtype;
};

#endif //__PARTICLE_H__
