#ifndef __SHOTCROUCHSTATE_H__
#define __SHOTCROUCHSTATE_H__

#include "PlayerState.h"

class ShotcrouchState : public PlayerState
{
public:
	ShotcrouchState();

	PlayerState* update(ModulePlayer& player);
	void enter(ModulePlayer& player);
	void OnCollision(Collider* c1, Collider* c2){};
};

#endif //__SHOTCROUCHSTATE_H__