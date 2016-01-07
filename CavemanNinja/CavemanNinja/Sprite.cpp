#include "Sprite.h"
#include "Animation.h"
#include "Collider.h"
#include "Application.h"
#include "ModuleCollisions.h"


Sprite::Sprite(bool active) : Module(active)
{}

Sprite::Sprite() : Module(true)
{}

void Sprite::SetCurrentAnimation(Animation* next_animation, bool alternate)
{
	previous_animation = current_animation;
	current_animation = next_animation;
	current_animation->alternate = alternate;

	if (next_animation != previous_animation) 
	{
		// delete colliders of the previous animation
		if (previous_animation != nullptr)
			for (auto& collider : previous_animation->colliders)
				collider->to_detach = true;

		// push colliders of the next animation
		if (current_animation != nullptr)
			for (auto& collider : current_animation->colliders)
			{
				App->collisions->AddCollider(collider);
			}

		current_animation->Reset();
	}
	// else, the player is just alternating it's animation version, no need to refresh colliders neither reseting animation
}

SDL_RendererFlip Sprite::Flip()
{
	if (direction == LEFT) return SDL_FLIP_HORIZONTAL;
	else return SDL_FLIP_NONE;
}

void Sprite::RefreshColliders()
{
	// if frame has changed, delete previous frame_colliders
	//                       add current frame_colliders
	if (previous_frame != current_frame)
	{
		// delete previous frame_colliders
		if (previous_frame != nullptr)
			for (auto& collider : (*previous_frame).colliders)
				collider->to_detach = true;

		// add current frame_colliders
		if (current_frame != nullptr)
			for (auto& collider : (*current_frame).colliders)
			{
				App->collisions->AddCollider(collider);
			}
	}
}

void Sprite::PlaceColliders()
{
	// moves the frame and animation colliders to the sprite position (+offset)

	if (current_frame != nullptr)
		for (auto& collider : (*current_frame).colliders)
			collider->SetPos((int)position.x, (int)position.y, CAN_FLIP);

	if (current_animation != nullptr)
		for (auto& collider : current_animation->colliders)
			collider->SetPos((int)position.x, (int)position.y, CAN_FLIP);
}