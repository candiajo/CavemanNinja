#include "SpritePlatform.h"
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
#include "ModuleHud.h"

bool ModuleSceneDino::Start()
{
	App->player1->Enable();
	App->particles->Enable();
	App->hud->Enable();

	LOG("Loading Title assets");

	texture_scene_dino = App->textures->Load(IMG_SCENE_DINO);
	App->audio->PlayMusic(MUSIC_BOSS_LEVEL);

	bgplatform_sprite = new SpritePlatform(texture_scene_dino, &bgplatform_animation);

	LoadData();

	bgplatform_sprite->Start();

	bgflowers.colliders.front()->SetPos((int)bgflowers.frames.front().offset.x, (int)bgflowers.frames.front().offset.y);
	App->collisions->AddCollider(bgflowers.colliders.front());	// adds the first (and only) collider

	timer = new Timer(2000);
	timer->StartTimer();

	dino_defeated = false;
	player_defeated = false;

	App->dino->energy = DINO_MAX_ENERGY;
	App->player1->energy = PLAYER_MAX_ENERGY;

	state = PLAY;

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
		else if (name == "bgplatform") StoreData(info, data, bgplatform_animation, bgplatform_sprite);
		else if (name == "bgflowers") StoreData(info, data, bgflowers, this);
		else if (name == "girl") StoreData(info, data, girl, this);
		else if (name == "gameover") StoreData(info, data, gameover, this);
		else if (name == "congratulations") StoreData(info, data, congratulations, this);
	}
}

update_status ModuleSceneDino::Update()
{
	DrawScenario();

	switch (state)
	{
	case PLAY:
		if (timer->TimeOver() && !App->dino->IsEnabled())
			App->dino->Enable();

		if (App->player1->player_end)
		{
			App->lives--;
			if (App->lives < 0)
			{
				timer->StartTimer(4000);
				App->dino->invulnerable = true;
				state = GAMEOVER;
			}
			else NextScene(this);
		}
		else if (dino_defeated)
		{
			timer->StartTimer(1000);
			App->player1->invulnerable = true;
			state = PRE_CONGRATULATIONS;
		}
		break;
	case PRE_CONGRATULATIONS:
		if (timer->TimeOver())
		{
			App->audio->PlayMusic(MUSIC_WIN);
			timer->StartTimer(7000);
			state = CONGRATULATIONS;
		}
		//no break;
	case GAMEOVER:
		//no break;
	case CONGRATULATIONS:
		if (timer->TimeOver()) NextScene(App->scene_title);
		break;
	}
	

	//todelete
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		NextScene(App->scene_title);
	}

	return UPDATE_CONTINUE;
}

update_status ModuleSceneDino::PostUpdate()
{
	int x, y;

	if (state == GAMEOVER)
	{
		x = (int)gameover.GetCurrentFrame().offset.x;
		y = (int)gameover.GetCurrentFrame().offset.y;
		App->renderer->Blit(texture_scene_dino, x, y, (gameover.GetCurrentFrame().section), SDL_FLIP_NONE);
	}
	else if (state == CONGRATULATIONS)
	{
		x = (int)congratulations.GetCurrentFrame().offset.x;
		y = (int)congratulations.GetCurrentFrame().offset.y;
		App->renderer->Blit(texture_scene_dino, x, y, (congratulations.GetCurrentFrame().section), SDL_FLIP_NONE);
	}
	return UPDATE_CONTINUE;
}

bool ModuleSceneDino::CleanUp()
{
	LOG("Unloading Title scene");

	App->textures->Unload(texture_scene_dino);
	App->audio->StopMusic();

	bgflowers.DestroyColliders();
	bgvolcanos.DestroyColliders();

	RELEASE(bgplatform_sprite);
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
	App->hud->Disable();
}

void ModuleSceneDino::DrawScenario()
{
	int x, y;

	x = (int)bgvolcanos.GetCurrentFrame().offset.x;
	y = (int)bgvolcanos.GetCurrentFrame().offset.y;
	App->renderer->Blit(texture_scene_dino, x, y, (bgvolcanos.GetCurrentFrame().section), SDL_FLIP_NONE);

	bgplatform_sprite->Update(App->dino->energy);

	//todelete
	/*x = (int)bgplatform.GetCurrentFrame().offset.x;
	y = (int)bgplatform.GetCurrentFrame().offset.y;
	App->renderer->Blit(texture_scene_dino, x, y, (bgplatform.GetCurrentFrame().section), SDL_FLIP_NONE);*/

	x = (int)bgflowers.GetCurrentFrame().offset.x;
	y = (int)bgflowers.GetCurrentFrame().offset.y;
	App->renderer->Blit(texture_scene_dino, x, y, (bgflowers.GetCurrentFrame().section), SDL_FLIP_NONE);

	x = (int)bgplatform_sprite->position.x + (int)girl.GetCurrentFrame().offset.x;
	y = (int)bgplatform_sprite->position.y + (int)girl.GetCurrentFrame().offset.y;
	App->renderer->Blit(texture_scene_dino, x, y, (girl.GetCurrentFrame().section), SDL_FLIP_NONE);
}