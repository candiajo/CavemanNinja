#ifndef __MODULEDINO_H__
#define __MODULEDINO_H__

#include "Sprite.h"
#include "Animation.h"

#define TIME_BETWEEN_BLINKS 4000

class DinoState;
class SpriteDinoBody;

class ModuleDino : public Sprite
{
public:
	ModuleDino(bool active) : Sprite(active) {};

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void CloseEye(int time);
	FrameInfo* getClosedEyeFrame();
	void OnCollision(Collider* my_collider, Collider* other_collider);

	void SetInvulnerable(int time);

	Animation openmouth;
	Animation closemouth;
	Animation semiopenmouth;
	Animation semiclosemouth;
	Animation superhit;
	Animation defeated;
	Animation eyeclosed1;
	Animation eyeclosed2;

	Animation dinobody;
	Animation dinobodyground;

	unsigned int fx_dino_defeated;
	unsigned int fx_dino_roar;
	unsigned int fx_enemy_hurt;
	unsigned int fx_weapon_hit;
	unsigned int fx_dino_stomps;
	unsigned int fx_dino_tail;

	SpriteDinoBody* spritedinobody;

	bool player_too_near;		// true when the player gets under de head

private:
	void LoadData();
	
	DinoState* state;
	bool eyeclosed;

	Timer* time_between_blinks;
};

#endif // __MODULEDINO_H__