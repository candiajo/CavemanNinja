#ifndef __PARTICLEARM_H__
#define __PARTICLEARM_H__

#include "Particle.h"

#define JUMP_OFFSET_Y -4
#define CROUCH_OFFSET_X 7
#define CROUCH_OFFSET_Y 11

class Animation;
class ModulePlayer;

enum arm_state
{
	ARM_SLOW_1,
	ARM_SLOW_2,
	ARM_FAST_1,
	ARM_FAST_2,
	TIRED,
	ARM_STOP
};

class ParticleArm : public Particle
{
public:
	ParticleArm(particle_type type, Sprite* generator);
	~ParticleArm();

	void ParticleUpdate();
	arm_state state;

private:
	unsigned int fx_charging;
	int channel;				// of the sound played, for stopping it
	Animation* arm_slow;
	Animation* arm_fast;
	ModulePlayer* player;
};

#endif //__PARTICLEARM_H_