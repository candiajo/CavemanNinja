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
	LoadData();

	state = new AgressiveAttackState();
	state->enter(*this);

	position.x = -120;
	position.y = 15;

	eyeclosed = false;
	
	timebetweenblinks = new Timer(TIME_BETWEEN_BLINKS);
	timebetweenblinks->StartTimer();

	spritedinobody = new SpriteDinoBody(texture_sprite);
	spritedinobody->Start();

	return true;
}

update_status ModuleDino::Update()
{
	SDL_Rect frame_section;
	DinoState* temp_state = state->update(*this);

	if (temp_state != nullptr)
	{
		delete state;
		state = temp_state;

		state->enter(*this);
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
			delete timer;
			eyeclosed = false;
			timebetweenblinks->StartTimer();
		}
	}
	else if (timebetweenblinks->TimeOver()) CloseEye(DINO_BLINK);
	
	// draw head over body
	spritedinobody->Update(position);
	App->renderer->Blit(texture_sprite, (int)position.x, (int)position.y, &frame_section, SDL_FLIP_NONE);

	return UPDATE_CONTINUE;
}

update_status ModuleDino::PostUpdate()
{
	previous_frame = current_frame;

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
	dinobody.DestroyColliders();
	dinobodyground.DestroyColliders();

	delete spritedinobody;
	
	if (timebetweenblinks != nullptr) delete timebetweenblinks;
	if (state != nullptr) delete state;

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
		else if (name == "dinobody") StoreData(info, data, dinobody, this);
		else if (name == "dinobodyground") StoreData(info, data, dinobodyground, this);
	}
}

void ModuleDino::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_PLAYER_BODY) 
		player_too_near = true;
}

void ModuleDino::CloseEye(int time)
{
	timer = new Timer(time);
	timer->StartTimer();
	eyeclosed = true;
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