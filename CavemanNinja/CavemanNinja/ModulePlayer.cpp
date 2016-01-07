#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Animation.h"
#include "File.h"
#include "PlayerState.h"
#include "JumpState.h"
#include "IdleState.h"
#include "Collider.h"
#include "ModuleCollisions.h"
#include "ModuleInput.h"

bool ModulePlayer::Start()
{
	direction = RIGHT;
	LOG("Loading player");

	texture_sprite = App->textures->Load(IMG_PLAYER);
	LoadData();
	
	state = new JumpState(FALLING);
	state->enter(*this);

	position.x = 50;
	position.y = 0;

	energy = 18;

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

	current_frame = &(*current_animation).GetCurrentFrame();
	position.x += x_speed;
	position.y += y_speed;
	RefreshColliders();
	PlaceColliders();
	
	Point temp_position = position;
	temp_position.y += current_frame->offset.y;
	if (direction == LEFT) temp_position.x -= current_frame->offset.x;
	else temp_position.x += current_frame->offset.x;

	App->renderer->Blit(texture_sprite, (int)temp_position.x, (int)temp_position.y, current_frame->section, Flip());
	
	return UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	previous_frame = current_frame;

	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	idle.DestroyColliders();
	walk.DestroyColliders();
	crouch.DestroyColliders();
	lookup.DestroyColliders();
	normaljump.DestroyColliders();
	superjump.DestroyColliders();
	downjump.DestroyColliders();
	shotweapon.DestroyColliders();
	shotcrouch.DestroyColliders();
	shotup.DestroyColliders();
	frontattack.DestroyColliders();
	backattack.DestroyColliders();
	frontdying.DestroyColliders();
	backdying.DestroyColliders();
	salute.DestroyColliders();
	tired.DestroyColliders();

	if (state != nullptr) delete state;
	return true;
}

void ModulePlayer::LoadData()
{
	std::string name;
	info_type info;
	GenericData data;

	File player_data(DATA_PLAYER);

	while (player_data.GetAnimInfo(info, name, data))
	{
		if (name == "crouch") StoreData(info, data, crouch, this);
		else if (name == "idle") StoreData(info, data, idle, this);
		else if (name == "lookup") StoreData(info, data, lookup, this);
		else if (name == "walk") StoreData(info, data, walk, this);
		else if (name == "normaljump") StoreData(info, data, normaljump, this);
		else if (name == "superjump") StoreData(info, data, superjump, this);
		else if (name == "downjump") StoreData(info, data, downjump, this);
		else if (name == "shotweapon") StoreData(info, data, shotweapon, this);
		else if (name == "shotcrouch") StoreData(info, data, shotcrouch, this);
		else if (name == "shotup") StoreData(info, data, shotup, this);
		else if (name == "frontattack") StoreData(info, data, frontattack, this);
		else if (name == "backattack") StoreData(info, data, backattack, this);
		else if (name == "frontdying") StoreData(info, data, frontdying, this);
		else if (name == "backdying") StoreData(info, data, backdying, this);
		else if (name == "ch.idle") StoreData(info, data, ch_idle, this);
		else if (name == "ch.walk") StoreData(info, data, ch_walk, this);
		else if (name == "ch.crouch") StoreData(info, data, ch_crouch, this);
		else if (name == "ch.lookup") StoreData(info, data, ch_lookup, this);
		else if (name == "ch.normaljump") StoreData(info, data, ch_normaljump, this);
		else if (name == "ch.downjump") StoreData(info, data, ch_downjump, this);
		else if (name == "salute") StoreData(info, data, salute, this);
		else if (name == "tired") StoreData(info, data, tired, this);
		else if (name == "supershot") StoreData(info, data, supershot, this);
	}

	idle.SetAlternateVersion(&ch_idle);
	walk.SetAlternateVersion(&ch_walk);
	crouch.SetAlternateVersion(&ch_crouch);
	lookup.SetAlternateVersion(&ch_lookup);
	normaljump.SetAlternateVersion(&ch_normaljump);
	downjump.SetAlternateVersion(&ch_downjump);
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	state->OnCollision(c1, c2);
}