#include "Application.h"
#include "ModuleDino.h"
#include "DinoState.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Animation.h"
#include "File.h"
#include "Collider.h"
#include "ModuleCollisions.h"
#include "ModuleInput.h"
#include "AgressiveAttackState.h"
//#include "MoveState.h"

bool ModuleDino::Start()
{
	LOG("Loading dino");

	texture_sprite = App->textures->Load(IMG_DINO);
	LoadData();

	state = new AgressiveAttackState();
	state->enter(*this);

	position.x = -120;
	position.y = 15;

	return true;
}

update_status ModuleDino::Update()
{
	DinoState* temp_state = state->update(*this);

	if (temp_state != nullptr)
	{
		delete state;
		state = temp_state;

		state->enter(*this);
	}

	current_frame = &(*current_animation).GetCurrentFrame();
	RefreshColliders();
	PlaceColliders();
	App->renderer->Blit(texture_sprite, (int)position.x, (int)position.y, &(*current_frame).section, Flip());

	return UPDATE_CONTINUE;
}

update_status ModuleDino::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleDino::CleanUp()
{
	return UPDATE_CONTINUE;
}

void ModuleDino::LoadData()
{
	std::string name;
	info_type info;
	GenericData data;

	File dino_data(DATA_DINO);

	while (dino_data.GetAnimInfo(info, name, data))
	{
		if (name == "openmouth") StoreData(info, data, openmouth, this);
		else if (name == "closemouth") StoreData(info, data, closemouth, this);
		else if (name == "semiopenmouth") StoreData(info, data, semiopenmouth, this);
		else if (name == "semiclosemouth") StoreData(info, data, semiclosemouth, this);
		else if (name == "superhit") StoreData(info, data, superhit, this);
		else if (name == "defeated") StoreData(info, data, defeated, this);
	}
}

void ModuleDino::OnCollision(Collider* c1, Collider* c2)
{}