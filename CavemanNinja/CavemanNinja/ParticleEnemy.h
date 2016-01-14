#ifndef __PARTICLEENEMY_H__
#define __PARTICLEENEMY_H__

#include "Particle.h"

class Animation;

enum enemy_state
{
	ENEMY_BOUNCING,
	ENEMY_HIT,
	ENEMY_DEFEATED
};

class ParticleEnemy : public Particle
{
public:
	ParticleEnemy(particle_type type, Sprite* generator);
	~ParticleEnemy();

	void ParticleUpdate();
	void OnCollision(Collider* my_collider, Collider* other_collider);

private:
	Animation* rollingenemy_animation;
	Animation* hitenemy_animation;
	Animation* defeatedenemy_animation;
	enemy_state state;
	collider_type first_bounce;
	int bounces = 0;
	unsigned int fx_enemy_hurt;
	unsigned int fx_weapon_hit;
};

#endif //__PARTICLEENEMY_H__