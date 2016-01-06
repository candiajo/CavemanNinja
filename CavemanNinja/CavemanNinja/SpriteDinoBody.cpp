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

bool SpriteDinoBody::Start()
{
	dinobody_animation = &App->dino->dinobody;
	dinobodyground_animation = &App->dino->dinobodyground;

	SetCurrentAnimation(dinobody_animation);
	
	return true;
}

update_status SpriteDinoBody::Update(Point head_position)
{
	position = head_position;
	current_frame = &(*current_animation).GetCurrentFrame();
	
	position.x += BODY_X_OFFSET;
	position.y += BODY_Y_OFFSET;

	PlaceColliders();
	position = head_position;
	App->renderer->Blit(texture_sprite, (int)position.x + BODY_X_OFFSET, (int)position.y + BODY_Y_OFFSET, &(*current_frame).section, SDL_FLIP_NONE);

	return UPDATE_CONTINUE;
}

void SpriteDinoBody::OnCollision(Collider* c1, Collider* c2)
{}