#include "Application.h"
#include "ModuleBeginLevel.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

#include "SDL.h"
#include "SDL_Timer.h"

ModuleBeginLevel::ModuleBeginLevel(bool active) : Module(active)
{}

ModuleBeginLevel::~ModuleBeginLevel()
{}

bool ModuleBeginLevel::Start()
{
	int w, h;

	LOG("Loading transition assets");
	texture_ready = App->textures->Load(IMG_READY);
	
	if (texture_ready != nullptr)
	{
		// gets the coords for centering the image on screen
		SDL_QueryTexture(texture_ready, NULL, NULL, &w, &h);
		center_x = (SCREEN_WIDTH / 2) - (w / 2);
		center_y = (SCREEN_HEIGHT / 2) - (h / 2);

		return true;
	}
	else
	{
		return false;
	}
}

update_status ModuleBeginLevel::Update()
{
	if (transition_running)
	{
		if (SDL_GetTicks() > (start_time + total_time))
		{
			if (next_scene != nullptr) next_scene->Enable();
			transition_running = false;
		}
		else
		{
			App->renderer->Blit(texture_ready, center_x, center_y, NULL, SDL_FLIP_NONE);
		}
	}
	return UPDATE_CONTINUE;
}

void ModuleBeginLevel::Transition(Module* next_scene, Module* previous_scene, Uint32 time)
{
	transition_running = true;
	start_time = SDL_GetTicks();
	total_time = time  * 1000;

	this->next_scene = next_scene;

	if (previous_scene != nullptr) previous_scene->Disable();
}