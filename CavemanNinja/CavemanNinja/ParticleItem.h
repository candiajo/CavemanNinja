#ifndef __PARTICLEITEM_H__
#define __PARTICLEITEM_H__

#include "Particle.h"

class Animation;

class ParticleItem : public Particle
{
public:
	ParticleItem(particle_type type);
	~ParticleItem();

	void ParticleUpdate();
	void OnCollision(Collider* my_collider, Collider* other_collider);

private:
	unsigned int fx_take_item;
	Timer* delay;
	Animation* item_animation;
	weapon_type weapon;
};

#endif //__PARTICLEITEM_H__