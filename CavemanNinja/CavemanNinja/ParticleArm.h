#ifndef __PARTICLEARM_H__
#define __PARTICLEARM_H__

#include "Particle.h"

#define JUMP_OFFSET_Y -4
#define CROUCH_OFFSET_X 7
#define CROUCH_OFFSET_Y 11

class Animation;

enum arm_state
{
	ARM_SLOW_1,
	ARM_SLOW_2,
	ARM_FAST_1,
	ARM_FAST_2,
	TIRED
};

class ParticleArm : public Particle
{
public:
	ParticleArm(particle_type type, Sprite* generator);
	~ParticleArm();

	void ParticleUpdate();

private:
	Animation* arm_slow;
	Animation* arm_fast;
	arm_state state;
	ModulePlayer* player;
};

#endif //__PARTICLEARM_H_