#include "ModuleSprite.h"
#include "Animation.h"
#include "Collider.h"
#include "Application.h"
#include "ModuleCollisions.h"

ModuleSprite::ModuleSprite(bool active) : Module(active)
{}

void ModuleSprite::SetCurrentAnimation(Animation* next_animation)
{
	previous_animation = current_animation;
	current_animation = next_animation;
	current_animation->Reset();
}

SDL_RendererFlip ModuleSprite::Flip()
{
	if (direction == LEFT) return SDL_FLIP_HORIZONTAL;
	else return SDL_FLIP_NONE;
}

void ModuleSprite::RefreshColliders()
{
	// if frame has changed, delete previous frame_colliders and animation_colliders
	//                       add current frame_colliders and animation_colliders
	if (previous_frame != current_frame)
	{
		// delete previous frame_colliders
		if (previous_frame != nullptr)
			for (auto& collider : (*previous_frame).colliders)
				collider->to_delete = true;

		// add current frame_colliders
		if (current_frame != nullptr)
			for (auto& collider : (*current_frame).colliders)
			{
				//collider->SetPos((int)position.x, (int)position.y);
				App->collisions->AddCollider(collider);
			}

		// delete colliders of the previous animation
		if (previous_animation != nullptr)
			for (auto& collider : previous_animation->colliders)
				collider->to_delete = true;

		// push colliders of the next animation
		if (current_animation != nullptr)
			for (auto& collider : current_animation->colliders)
			{
				//collider->SetPos((int)position.x, (int)position.y);
				App->collisions->AddCollider(collider);
			}
	}
}

void ModuleSprite::PlaceColliders()
{
	// moves the frame and animation colliders to the sprite position (+offset)

	if (current_frame != nullptr)
		for (auto& collider : (*current_frame).colliders)
			collider->SetPos((int)position.x, (int)position.y, CAN_FLIP);

	if (current_animation != nullptr)
		for (auto& collider : current_animation->colliders)
			collider->SetPos((int)position.x, (int)position.y, CAN_FLIP);
}