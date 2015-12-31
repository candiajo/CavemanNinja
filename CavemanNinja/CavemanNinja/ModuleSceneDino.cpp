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

#include "SDL.h"

ModuleSceneDino::ModuleSceneDino(bool start_enabled) : Module(start_enabled)
{}

ModuleSceneDino::~ModuleSceneDino()
{}

bool ModuleSceneDino::Start()
{
	LOG("Loading Title assets");

	texture_scene_dino = App->textures->Load(IMG_SCENE_DINO);
	//App->audio->PlayMusic("intro.ogg", 0.0f);
	//fx = App->audio->LoadFx("starting.wav");

	LoadData();	// load .ini data

	return (texture_scene_dino != nullptr);
}

void ModuleSceneDino::LoadData()
{
	std::string name;
	Frame_info frame;

	File background_data(DATA_SCENE_DINO);

	while (background_data.GetFrameInfo(name, frame))
	{
		if (name == "bgvolcanos")
		{
			bgvolcanos = frame;
		}
		else if (name == "bgplatform")
		{
			bgplatform = frame;
		}
		else if (name == "bgflowers")
		{
			bgflowers = frame;
		}
		else if (name == "girl")
		{
			// girl frames
		}
	}
}

update_status ModuleSceneDino::Update()
{
	App->renderer->Blit(texture_scene_dino, bgvolcanos.x_offset, bgvolcanos.y_offset, &bgvolcanos.section);
	App->renderer->Blit(texture_scene_dino, bgplatform.x_offset, bgplatform.y_offset, &bgplatform.section);
	App->renderer->Blit(texture_scene_dino, bgflowers.x_offset, bgflowers.y_offset, &bgflowers.section);

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

	return true;
}
