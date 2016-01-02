#include "Collider.h"
#include "ModuleSprite.h"

Collider::Collider(SDL_Rect rectangle, Point& offset, int frame_w, collider_type type, Module* callback = nullptr) :
rect(rectangle),
offset(offset),
frame_w(frame_w),
type(type),
callback(callback),
to_delete(false)
{}

void Collider::SetPos(int x, int y, bool can_flip)
{
	Point temp_offset = offset;

	if (can_flip)
	{
		if (dynamic_cast<ModuleSprite*>(callback)->direction == LEFT)
		{
			temp_offset.x = (frame_w - rect.w / 2 - offset.x / 2 + 1) * 2;
		}
	}

	rect.x = (x * SCREEN_SIZE) + temp_offset.x;
	rect.y = (y * SCREEN_SIZE) + temp_offset.y;
}

bool Collider::IsColliding(Collider* collider) const
{
	SDL_Rect discard;

	return SDL_IntersectRect(&rect, &(collider->rect), &discard);
}

Point Collider::GetOffset()
{
	Point temp_offset = offset;
	if (dynamic_cast<ModuleSprite*>(callback)->direction == LEFT)
	{
		temp_offset.x = (frame_w - rect.w / 2 - offset.x / 2 + 1) * 2;
	}
	
	return temp_offset;
}