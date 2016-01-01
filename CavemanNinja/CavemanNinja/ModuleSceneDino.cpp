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

ModuleSceneDino::ModuleSceneDino(bool active) : Module(active)
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
	float speed;
	bool loop;
	info_type info;

	File background_data(DATA_SCENE_DINO);

	while (background_data.GetAnimInfo(info, name, frame, speed, loop))
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
			switch (info)
			{
			case FRAME_INFO: girl.frames.push_back(frame);	break;
			case SPEED_INFO: girl.speed = speed;			break;
			case LOOP_INFO: girl.loop = loop;				break;
			}
		}
	}
}

update_status ModuleSceneDino::Update()
{
	int x_girl = girl.GetCurrentFrame().x_offset;
	int y_girl = girl.GetCurrentFrame().y_offset;

	App->renderer->Blit(texture_scene_dino, bgvolcanos.x_offset, bgvolcanos.y_offset, &bgvolcanos.section);
	App->renderer->Blit(texture_scene_dino, bgplatform.x_offset, bgplatform.y_offset, &bgplatform.section);
	App->renderer->Blit(texture_scene_dino, bgflowers.x_offset, bgflowers.y_offset, &bgflowers.section);
	App->renderer->Blit(texture_scene_dino, x_girl, y_girl, &(girl.GetCurrentFrame().section));

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
