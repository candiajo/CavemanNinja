#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Animation.h"
#include "File.h"
#include "PlayerState.h"
#include "IdleState.h"
#include "CrouchState.h"

#include "ModuleInput.h"
#include "SDL.h"


ModulePlayer::ModulePlayer(bool active) : Module(active)
{
	state = new IdleState();
	state->enter(*this);
}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::Start()
{
	LOG("Loading player");

	texture_player = App->textures->Load(IMG_PLAYER);
	LoadData();

	//todelete
	position.x = 0;
	position.y = 215-59;

	return true;
}

update_status ModulePlayer::Update()
{
	PlayerState* temp_state = state->update(*this);

	if (temp_state != nullptr)
	{
		delete state;
		state = temp_state;

		state->enter(*this);
	}

	position.x += x_speed;
	position.y += y_speed;
	App->renderer->Blit(texture_player, (int)position.x, (int)position.y, &((*current_animation).GetCurrentFrame().section));

	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	if (state != nullptr) delete state;
	return true;
}

void ModulePlayer::LoadData()
{
	std::string name;
	Frame_info frame;
	float speed;
	bool loop;
	info_type info;

	File player_data(DATA_PLAYER);

	while (player_data.GetAnimInfo(info, name, frame, speed, loop))
	{
		if (name == "crouch")
		{
			switch (info)
			{
			case FRAME_INFO: crouch.frames.push_back(frame);	break;
			case SPEED_INFO: crouch.speed = speed;				break;
			case LOOP_INFO: crouch.loop = loop;					break;
			}
		}
		else if (name == "idle")
		{
			switch (info)
			{
			case FRAME_INFO: idle.frames.push_back(frame);	break;
			case SPEED_INFO: idle.speed = speed;			break;
			case LOOP_INFO: idle.loop = loop;				break;
			}
		}
		else if (name == "lookup")
		{
			switch (info)
			{
			case FRAME_INFO: lookup.frames.push_back(frame);	break;
			case SPEED_INFO: lookup.speed = speed;				break;
			case LOOP_INFO: lookup.loop = loop;					break;
			}
		}
		else if (name == "walk")
		{
			switch (info)
			{
			case FRAME_INFO: walk.frames.push_back(frame);	break;
			case SPEED_INFO: walk.speed = speed;			break;
			case LOOP_INFO: walk.loop = loop;				break;
			}
		}
	}
}