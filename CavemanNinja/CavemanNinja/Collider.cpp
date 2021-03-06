#include "Collider.h"
#include "Sprite.h"
#include "ParticleAxe.h"

Collider::Collider(SDL_Rect rectangle, Point& offset, int frame_w, collider_type type, Module* callback = nullptr) :
rect(rectangle),
offset(offset),
frame_w(frame_w),
type(type),
callback(callback),
to_detach(false)
{}

void Collider::SetPos(int x, int y, bool can_flip)
{
	Point temp_offset = offset;

	if (can_flip)
	{
		if (dynamic_cast<Sprite*>(callback)->direction == LEFT)
		{
			temp_offset.x = (frame_w - rect.w / SCREEN_SIZE - offset.x / SCREEN_SIZE + 1) * SCREEN_SIZE;
		}
	}

	rect.x = (x * SCREEN_SIZE) + (int)temp_offset.x;
	rect.y = (y * SCREEN_SIZE) + (int)temp_offset.y;
}

bool Collider::IsColliding(Collider* collider) const
{
	SDL_Rect discard;

	return SDL_IntersectRect(&rect, &(collider->rect), &discard);
}

Point Collider::GetOffset() const
{
	Point temp_offset = offset;
	if (dynamic_cast<Sprite*>(callback)->direction == LEFT)
	{
		temp_offset.x = (frame_w - rect.w / 2 - offset.x / 2 + 1) * 2;
	}
	return temp_offset;
}