#include "Globals.h"
#include "Application.h"
#include "ModuleSceneTitle.h"
#include "ModuleSceneDino.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleBeginLevel.h"
#include "ModuleAudio.h"

#include "SDL.h"


bool ModuleSceneTitle::Start()
{
	LOG("Loading Title assets");

	texture_title = App->textures->Load(IMG_TITLE_SCREEN);
	fx_begin_play = App->audio->LoadFx(FX_BEGIN_PLAY);

	App->lives = PLAYER_MAX_LIVES;

	return (texture_title != nullptr);
}

update_status ModuleSceneTitle::Update()
{
	// Draw title screen -------------------------------------
	App->renderer->Blit(texture_title, 0, 0, NULL, SDL_FLIP_NONE);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->begin_level->Transition(App->scene_dino, this, 1);
		App->audio->PlayFx(fx_begin_play);
	}

	return UPDATE_CONTINUE;
}

bool ModuleSceneTitle::CleanUp()
{
	LOG("Unloading Title scene");

	App->textures->Unload(texture_title);

	return true;
}
