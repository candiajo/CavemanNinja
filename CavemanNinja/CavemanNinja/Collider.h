#ifndef __MODULECOLLIDER_H__
#define __MODULECOLLIDER_H__

#include "Globals.h"
#include "Module.h"

struct SDL_Rect;

class Collider
{
public:
	Collider(SDL_Rect rectangle, int x_offset, int y_offset, collider_type type, Module* callback);

	void SetPos(int x, int y, bool scaled = true);
	bool IsColliding(Collider* collider) const;

	SDL_Rect rect;
	int x_offset, y_offset;
	bool to_delete;
	collider_type type;
	Module* callback;
};

#endif // __MODULECOLLIDER_H__