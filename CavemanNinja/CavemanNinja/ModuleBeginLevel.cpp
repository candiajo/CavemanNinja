#include "Application.h"
#include "ModuleBeginLevel.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "File.h"
#include "SDL.h"
#include "Timer.h"

ModuleBeginLevel::~ModuleBeginLevel()
{
	RELEASE(timer);
}

bool ModuleBeginLevel::Start()
{
	LoadData();
	timer = new Timer(1000);
	current = &ready;

	return true;
}

update_status ModuleBeginLevel::Update()
{
	if (transition_running)
	{
		if (timer->TimeOver())
		{
			if (next_scene != nullptr) next_scene->Enable();
			transition_running = false;
		}
		else
		{
			FrameInfo* frame = &current->GetCurrentFrame();

			App->renderer->Blit(texture_transition, (int)frame->offset.x, (int)frame->offset.y, frame->section, SDL_FLIP_NONE);
		}
	}
	return UPDATE_CONTINUE;
}

void ModuleBeginLevel::Transition(Module* next_scene, Module* previous_scene, Uint32 time)
{
	transition_running = true;
	
	this->next_scene = next_scene;

	if (previous_scene != nullptr) previous_scene->Disable();

	if (next_scene == (Module*)App->scene_title)
	{
		timer->StartTimer(2000);
		current = &scoretable;
	}
	else
	{
		timer->StartTimer(1000);
		current = &ready;
	}
}

void ModuleBeginLevel::LoadData()
{
	std::string name;
	info_type info;
	GenericData data;

	LOG("Loading transition assets");
	texture_transition = App->textures->Load(IMG_TRANSITION);

	File player_data(DATA_TRANSITION);

	while (player_data.GetAnimInfo(info, name, data))
	{
		if (name == "ready") StoreData(info, data, ready, this);
		if (name == "scoretable") StoreData(info, data, scoretable, this);
	}

}