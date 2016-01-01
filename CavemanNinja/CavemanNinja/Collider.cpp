#include "Collider.h"

Collider::Collider(SDL_Rect rectangle, int x_offset, int y_offset, collider_type type, Module* callback = nullptr) :
rect(rectangle),
x_offset(x_offset),
y_offset(y_offset),
type(type),
callback(callback),
to_delete(false)
{}

void Collider::SetPos(int x, int y, bool scaled)
{
	if (scaled)
	{
		rect.x = (x * SCREEN_SIZE) + x_offset;
		rect.y = (y * SCREEN_SIZE) + y_offset;
	}
	else
	{
		rect.x = x + x_offset;
		rect.y = y + y_offset;
	}
}

bool Collider::IsColliding(Collider* collider) const
{
	SDL_Rect discard;

	return SDL_IntersectRect(&rect, &(collider->rect), &discard);
}