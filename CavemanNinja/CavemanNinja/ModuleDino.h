#ifndef __MODULEDINO_H__
#define __MODULEDINO_H__

#include "Sprite.h"
#include "Animation.h"

class DinoState;
class SpriteDinoBody;

class ModuleDino : public Sprite
{
public:
	ModuleDino(bool active) : Sprite(active) {};
	~ModuleDino() {};

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

	Animation openmouth;
	Animation closemouth;
	Animation semiopenmouth;
	Animation semiclosemouth;
	Animation superhit;
	Animation defeated;
	Animation dinobody;

	SpriteDinoBody* spritedinobody;

	bool player_too_near;		// true when the player gets under de head

private:
	void LoadData();
	DinoState* state;
};

#endif // __MODULEDINO_H__