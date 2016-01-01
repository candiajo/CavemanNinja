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

ModulePlayer::ModulePlayer(bool active) : Module(active)
{
	state = new IdleState();
	state->enter(*this);
}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::Start()
{
	direction = RIGHT;
	LOG("Loading player");

	texture_player = App->textures->Load(IMG_PLAYER);
	LoadData();

	//todelete
	position.x = 100;
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
	App->renderer->Blit(texture_player, (int)position.x, (int)position.y, &((*current_animation).GetCurrentFrame().section), Flip());

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
	info_type info;
	Generic_data data;

	File player_data(DATA_PLAYER);

	while (player_data.GetAnimInfo(info, name, data))
	{
		if (name == "crouch") StoreData(info, data, crouch, this);
		else if (name == "idle") StoreData(info, data, idle, this);
		else if (name == "lookup") StoreData(info, data, lookup, this);
		else if (name == "walk") StoreData(info, data, walk, this);
	}
}

SDL_RendererFlip ModulePlayer::Flip()
{
	if (direction == LEFT) return SDL_FLIP_HORIZONTAL;
	else return SDL_FLIP_NONE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{

}