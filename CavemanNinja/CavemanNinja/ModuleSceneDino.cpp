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
#include "ModulePlayer.h"
#include "ModuleDino.h"
#include "ModuleParticles.h"
#include "Timer.h"
#include "SDL.h"
#include "ModuleAudio.h"

bool ModuleSceneDino::Start()
{
	App->player1->Enable();
	App->particles->Enable();

	player_defeated = false;

	LOG("Loading Title assets");

	texture_scene_dino = App->textures->Load(IMG_SCENE_DINO);
	//App->audio->PlayMusic(MUSIC_BOSS_LEVEL);

	LoadData();

	bgplatform.colliders.front()->SetPos((int)bgplatform.frames.front().offset.x, (int)bgplatform.frames.front().offset.y);
	bgplatform.colliders.back()->SetPos((int)bgplatform.frames.back().offset.x, (int)bgplatform.frames.back().offset.y);
	App->collisions->AddCollider(bgplatform.colliders.front());	// adds the first colliders
	App->collisions->AddCollider(bgplatform.colliders.back());	// adds the second collider

	bgflowers.colliders.front()->SetPos((int)bgflowers.frames.front().offset.x, (int)bgflowers.frames.front().offset.y);
	App->collisions->AddCollider(bgflowers.colliders.front());	// adds the first (and only) collider

	timer = new Timer(2000);
	timer->StartTimer();

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
	if (timer->TimeOver() && !App->dino->IsEnabled()) App->dino->Enable();

	int x = (int)bgvolcanos.GetCurrentFrame().offset.x;
	int y = (int)bgvolcanos.GetCurrentFrame().offset.y;
	App->renderer->Blit(texture_scene_dino, x, y, (bgvolcanos.GetCurrentFrame().section), SDL_FLIP_NONE);

	x = (int)bgplatform.GetCurrentFrame().offset.x;
	y = (int)bgplatform.GetCurrentFrame().offset.y;
	App->renderer->Blit(texture_scene_dino, x, y, (bgplatform.GetCurrentFrame().section), SDL_FLIP_NONE);

	x = (int)bgflowers.GetCurrentFrame().offset.x;
	y = (int)bgflowers.GetCurrentFrame().offset.y;
	App->renderer->Blit(texture_scene_dino, x, y, (bgflowers.GetCurrentFrame().section), SDL_FLIP_NONE);

	x = (int)girl.GetCurrentFrame().offset.x;
	y = (int)girl.GetCurrentFrame().offset.y;
	App->renderer->Blit(texture_scene_dino, x, y, (girl.GetCurrentFrame().section), SDL_FLIP_NONE);
	
	if (player_defeated) NextScene(this);
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		NextScene(App->scene_title);
		//App->audio->PlayFx(fx);
	}

	return UPDATE_CONTINUE;
}

bool ModuleSceneDino::CleanUp()
{
	LOG("Unloading Title scene");

	App->textures->Unload(texture_scene_dino);

	bgflowers.DestroyColliders();
	bgvolcanos.DestroyColliders();
	bgplatform.DestroyColliders();

	RELEASE(timer);
	return true;
}

void ModuleSceneDino::NextScene(Module* scene)
{
	App->begin_level->Transition(scene, this, 1);
	App->player1->Disable();
	App->particles->Disable();
	App->dino->Disable();
	App->collisions->CleanUp();
}