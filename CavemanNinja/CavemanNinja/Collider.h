#ifndef __MODULECOLLIDER_H__
#define __MODULECOLLIDER_H__

#include "Globals.h"
#include "Module.h"

#include <list>

struct SDL_Rect;

class Collider
{
public:
	Collider(SDL_Rect rectangle, Point& offset, int frame_w, collider_type type, Module* callback);

	void SetPos(int x, int y, bool can_flip = false);
	bool IsColliding(Collider* collider) const;
	Point GetOffset();

	SDL_Rect rect;
	bool to_detach = false;		// only detach from the list
	bool to_destroy = false;	// destroy the collider from memory
	collider_type type;
	Module* callback;

private:
	Point offset;
	int frame_w;	// needed for collider flipping
};

#endif // __MODULECOLLIDER_H__