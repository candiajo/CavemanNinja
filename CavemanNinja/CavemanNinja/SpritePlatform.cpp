#include "SpritePlatform.h"
#include "ModuleRender.h"
#include "Application.h"

SpritePlatform::SpritePlatform(SDL_Texture* sprite_texture, Animation* animation)
{
	this->texture_sprite = sprite_texture;
	bgplatform_animation = animation;
}

SpritePlatform::~SpritePlatform() 
{
	bgplatform_animation->DestroyColliders(); 
};

bool SpritePlatform::Start()
{
	SetCurrentAnimation(bgplatform_animation);

	position.x = bgplatform_animation->PeekFrame(0).offset.x;
	position.y = bgplatform_animation->PeekFrame(0).offset.y;

	y_original = position.y;

	RefreshColliders();
	PlaceColliders();

	return true;
}

update_status SpritePlatform::Update(int dino_energy)
{
	int lost_energy = DINO_MAX_ENERGY - dino_energy;
	float platform_target_position;

	if (lost_energy > 7) lost_energy = 7;
	platform_target_position = y_original + ((float)lost_energy * OFFSET_BY_HIT);

	current_frame = &bgplatform_animation->GetCurrentFrame();

	if (position.y < platform_target_position)
	{
		position.y += 0.5f;
		PlaceColliders();
	}

	App->renderer->Blit(texture_sprite, (int)position.x, (int)position.y, (*current_frame).section, SDL_FLIP_NONE);

	return UPDATE_CONTINUE;
}
