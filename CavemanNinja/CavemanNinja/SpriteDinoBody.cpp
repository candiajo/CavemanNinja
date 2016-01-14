#include "SpriteDinoBody.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleDino.h"
#include "ModuleRender.h"
#include "Application.h"

SpriteDinoBody::SpriteDinoBody(SDL_Texture* sprite_texture) : Sprite(active)
{
	this->texture_sprite = sprite_texture;
}

SpriteDinoBody::~SpriteDinoBody()
{
	dinobody_animation->ClearAnimation();
	dinobodyground_animation->ClearAnimation();
}

bool SpriteDinoBody::Start()
{
	damage = 4;

	dinobody_animation = &App->dino->dinobody;
	dinobodyground_animation = &App->dino->dinobodyground;

	SetCurrentAnimation(dinobody_animation);
	
	return true;
}

update_status SpriteDinoBody::Update(Point head_position)
{
	current_frame = &(*current_animation).GetCurrentFrame();
	
	position = head_position;
	position.x += current_frame->offset.x;
	position.y += current_frame->offset.y;

	PlaceColliders();

	App->renderer->Blit(texture_sprite, (int)position.x, (int)position.y, (*current_frame).section, SDL_FLIP_NONE);

	return UPDATE_CONTINUE;
}

void SpriteDinoBody::OnCollision(Collider* my_collider, Collider* other_collider)
{
	if (my_collider->type == COLLIDER_PROXIMITY && other_collider->type == COLLIDER_PLAYER_BODY)
		App->dino->player_too_near = true;
}