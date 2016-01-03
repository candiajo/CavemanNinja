#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Sprite.h"
#include "Animation.h"
#include "Globals.h"

class ModulePlayer : public Sprite
{
public:
	ModulePlayer(bool active = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

	Animation idle;
	Animation walk;
	Animation crouch;
	Animation lookup;
	Animation normaljump;
	Animation superjump;
	Animation downjump;
	Animation shotweapon;
	Animation shotcrouch;
	Animation shotup;

private:
	void LoadData();

};

#endif // __MODULEPLAYER_H__