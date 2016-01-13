#include "ParticleItem.h"
#include "Timer.h"
#include "ModuleParticles.h"
#include "Animation.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

ParticleItem::ParticleItem(particle_type type)
{
	timer = new Timer(9000);
	timer->StartTimer();

	item_animation = new Animation(App->particles->item_animation, this);

	SetCurrentAnimation(item_animation);
	
	if (type == ITEM_BONE) current_frame = &current_animation->PeekFrame(0);
	else if (type == ITEM_BOOMERANG) current_frame = &current_animation->PeekFrame(1);
	else if (type == ITEM_WHEEL) current_frame = &current_animation->PeekFrame(2);
	else if (type == ITEM_TUSK) current_frame = &current_animation->PeekFrame(3);

	switch (type)
	{
	case ITEM_WHEEL:
		current_frame = &current_animation->PeekFrame(2);
		weapon = WHEEL;
		break;
	case ITEM_BONE:
		current_frame = &current_animation->PeekFrame(0);
		weapon = BONE;
		break;
	case ITEM_BOOMERANG:
		current_frame = &current_animation->PeekFrame(1);
		weapon = BOOMERANG;
		break;
	case ITEM_TUSK:
		current_frame = &current_animation->PeekFrame(3);
		weapon = TUSK;
		break;
	}
	

	position.x = current_frame->offset.x;
	position.y = current_frame->offset.y;

	PlaceColliders();
}

ParticleItem::~ParticleItem()
{
	RELEASE(timer);
	RELEASE(item_animation);
}

void ParticleItem::ParticleUpdate()
{
	if (timer->TimeOver()) to_destroy = true;

	App->renderer->Blit(texture_sprite, (int)position.x, (int)position.y, current_frame->section, SDL_FLIP_NONE);
}

void ParticleItem::OnCollision(Collider* my_collider, Collider* other_collider)
{
	if (other_collider->type == COLLIDER_PLAYER_BODY)
	{
		dynamic_cast<ModulePlayer*>(other_collider->callback)->current_weapon = weapon;
		to_destroy = true;
	}
}