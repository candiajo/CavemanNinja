#include "Globals.h"
#include "Application.h"
#include "ModuleSceneTitle.h"
#include "ModuleSceneDino.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleBeginLevel.h"

#include "SDL.h"

ModuleSceneTitle::ModuleSceneTitle(bool active) : Module(active)
{}

ModuleSceneTitle::~ModuleSceneTitle()
{}

bool ModuleSceneTitle::Start()
{
	LOG("Loading Title assets");

	texture_title = App->textures->Load(IMG_TITLE_SCREEN);
	//App->audio->PlayMusic("intro.ogg", 0.0f);
	//fx = App->audio->LoadFx("starting.wav");

	return (texture_title != nullptr);
}

update_status ModuleSceneTitle::Update()
{
	// Draw title screen -------------------------------------
	App->renderer->Blit(texture_title, 0, 0, NULL);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->begin_level->Transition(App->scene_dino, this, 1);
		//App->audio->PlayFx(fx);
	}

	return UPDATE_CONTINUE;
}

bool ModuleSceneTitle::CleanUp()
{
	LOG("Unloading Title scene");

	App->textures->Unload(texture_title);

	return true;
}
