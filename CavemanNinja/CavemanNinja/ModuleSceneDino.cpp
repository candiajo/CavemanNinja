#include <string>
#include "Globals.h"
#include "Application.h"
#include "ModuleSceneDino.h"
#include "ModuleSceneTitle.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleBeginLevel.h"
#include "File.h"
#include "ModuleCollisions.h"
#include "Collider.h"

#include "SDL.h"

bool ModuleSceneDino::Start()
{
	LOG("Loading Title assets");

	texture_scene_dino = App->textures->Load(IMG_SCENE_DINO);
	//App->audio->PlayMusic("intro.ogg", 0.0f);
	//fx = App->audio->LoadFx("starting.wav");

	LoadData();	// load .ini data

	bgplatform.colliders.front()->SetPos(bgplatform.frames.front().offset.x, bgplatform.frames.front().offset.y);
	bgplatform.colliders.back()->SetPos(bgplatform.frames.back().offset.x, bgplatform.frames.back().offset.y);
	App->collisions->AddCollider(bgplatform.colliders.front());	// adds the first colliders
	App->collisions->AddCollider(bgplatform.colliders.back());	// adds the second collider

	bgflowers.colliders.front()->SetPos(bgflowers.frames.front().offset.x, bgflowers.frames.front().offset.y);
	App->collisions->AddCollider(bgflowers.colliders.front());	// adds the first (and only) collider
	return (texture_scene_dino != nullptr);
}

void ModuleSceneDino::LoadData()
{
	std::string name;
	info_type info;
	GenericData data;

	File background_data(DATA_SCENE_DINO);
	
	while (background_data.GetAnimInfo(info, name, data))
	{
		if (name == "bgvolcanos") StoreData(info, data, bgvolcanos, this);
		else if (name == "bgplatform") StoreData(info, data, bgplatform, this);
		else if (name == "bgflowers") StoreData(info, data, bgflowers, this);
		else if (name == "girl") StoreData(info, data, girl, this);
	}
}

update_status ModuleSceneDino::Update()
{
	int x = bgvolcanos.GetCurrentFrame().offset.x;
	int y = bgvolcanos.GetCurrentFrame().offset.y;
	App->renderer->Blit(texture_scene_dino, x, y, &(bgvolcanos.GetCurrentFrame().section), SDL_FLIP_NONE);

	x = bgplatform.GetCurrentFrame().offset.x;
	y = bgplatform.GetCurrentFrame().offset.y;
	App->renderer->Blit(texture_scene_dino, x, y, &(bgplatform.GetCurrentFrame().section), SDL_FLIP_NONE);

	x = bgflowers.GetCurrentFrame().offset.x;
	y = bgflowers.GetCurrentFrame().offset.y;
	App->renderer->Blit(texture_scene_dino, x, y, &(bgflowers.GetCurrentFrame().section), SDL_FLIP_NONE);

	x = girl.GetCurrentFrame().offset.x;
	y = girl.GetCurrentFrame().offset.y;
	App->renderer->Blit(texture_scene_dino, x, y, &(girl.GetCurrentFrame().section), SDL_FLIP_NONE);
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->begin_level->Transition(App->scene_title, this, 1);
		//App->audio->PlayFx(fx);
	}

	return UPDATE_CONTINUE;
}

bool ModuleSceneDino::CleanUp()
{
	LOG("Unloading Title scene");

	App->textures->Unload(texture_scene_dino);

	App->collisions->CleanUp();

	return true;
}
