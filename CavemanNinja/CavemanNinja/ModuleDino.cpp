#include "ModuleAudio.h"
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
#include "SpriteDinoBody.h"
#include "Timer.h"

bool ModuleDino::Start()
{
	LOG("Loading dino");

	texture_sprite = App->textures->Load(IMG_DINO);

	dinobody_sprite = new SpriteDinoBody(texture_sprite);

	LoadData();

	state = new AgressiveAttackState();
	state->Enter(*this);

	position.x = -120;
	position.y = 15;

	energy = DINO_MAX_ENERGY;
	damage = 4;

	eyeclosed = false;
	
	invulnerable_time = new Timer();
	time_between_blinks = new Timer(TIME_BETWEEN_BLINKS);
	time_between_blinks->StartTimer();

	dinobody_sprite->Start();

	return true;
}

update_status ModuleDino::Update()
{
	SDL_Rect* frame_section;
	DinoState* temp_state = state->Update(*this);

	if (temp_state != nullptr)
	{
		delete state;
		state = temp_state;

		state->Enter(*this);
	}

	current_frame = &(*current_animation).GetCurrentFrame();
	frame_section = current_frame->section;
	RefreshColliders();
	PlaceColliders();

	if (eyeclosed)
	{
		frame_section = getClosedEyeFrame()->section;
		if (timer->TimeOver())
		{
			RELEASE(timer);
			eyeclosed = false;
			time_between_blinks->StartTimer();
		}
	}
	else if (time_between_blinks->TimeOver()) CloseEye(DINO_BLINK);
	
	// draw head over body
	dinobody_sprite->Update(position);
	App->renderer->Blit(texture_sprite, (int)position.x, (int)position.y, frame_section, SDL_FLIP_NONE);

	return UPDATE_CONTINUE;
}

update_status ModuleDino::PostUpdate()
{
	previous_frame = current_frame;
	if (invulnerable_time->TimeOver()) invulnerable= false;

	return UPDATE_CONTINUE;
}

bool ModuleDino::CleanUp()
{
	openmouth.DestroyColliders();
	closemouth.DestroyColliders();
	semiopenmouth.DestroyColliders();
	semiclosemouth.DestroyColliders();
	superhit.DestroyColliders();
	defeated.DestroyColliders();
	eyeclosed1.DestroyColliders();
	eyeclosed2.DestroyColliders();

	RELEASE(dinobody_sprite);
	
	RELEASE(invulnerable_time);
	RELEASE(time_between_blinks);
	RELEASE(timer);
	RELEASE(state);

	return true;
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
		else if (name == "eyeclosed1") StoreData(info, data, eyeclosed1, this);
		else if (name == "eyeclosed2") StoreData(info, data, eyeclosed2, this);

		else if (name == "dinobody") StoreData(info, data, dinobody, dinobody_sprite);
		else if (name == "dinobodyground") StoreData(info, data, dinobodyground, dinobody_sprite);
	}

	fx_dino_defeated = App->audio->LoadFx(FX_DINO_DEFEATED);
	fx_dino_roar= App->audio->LoadFx(FX_DINO_ROAR);
	fx_enemy_hurt= App->audio->LoadFx(FX_ENEMY_HURT);
	fx_weapon_hit = App->audio->LoadFx(FX_WEAPON_HIT);
	fx_dino_roar = App->audio->LoadFx(FX_DINO_ROAR);
	fx_dino_stomps = App->audio->LoadFx(FX_DINO_STOPMS);
	fx_dino_tail = App->audio->LoadFx(FX_DINO_TAIL);
}

void ModuleDino::OnCollision(Collider* my_collider, Collider* other_collider)
{
	state->OnCollision(my_collider,other_collider);
}

void ModuleDino::CloseEye(int time)
{
	if (!eyeclosed)
	{
		timer = new Timer(time);
		timer->StartTimer();
		eyeclosed = true;
	}
}

// returns the "closedeye" frame equivalent to the current frame
FrameInfo* ModuleDino::getClosedEyeFrame() 
{
	int n = (int)current_animation->current_frame;

	if (current_animation == &openmouth || current_animation == &semiopenmouth)
		return &(eyeclosed1.PeekFrame(n));
	else if (current_animation == &closemouth)
		return &(eyeclosed2.PeekFrame(n));
	else if (current_animation == &semiclosemouth)
		return &(eyeclosed2.PeekFrame(n+2));
	else return current_frame;
}

