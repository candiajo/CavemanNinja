#include "ParticleArm.h"
#include "ModuleAudio.h"
#include "Timer.h"
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

	LoadData();
	
	state = new JumpState(FALLING);
	state->Enter(*this);

	position.x = 50;
	position.y = 0;

	invulnerable_time = new Timer();
	
	player_end = false;
	rolling_arm = false;
	is_crouch = false;
	is_tired = false;
	charge_enough = false;
	is_hit = false;
	is_defeated = false;

	hit_received_energy = 0;
	score = 0;

	return true;
}

update_status ModulePlayer::Update()
{
	PlayerState* temp_state = state->Update(*this);

	if (temp_state != nullptr)
	{
		delete state;
		state = temp_state;

		state->Enter(*this);
	}

	current_frame = &(*current_animation).GetCurrentFrame();
	position.x += x_speed;
	position.y += y_speed;

	if (position.x < LEFT_LIMIT) position.x = LEFT_LIMIT;
	if (position.x > RIGHT_LIMIT) position.x = RIGHT_LIMIT;

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
	if (invulnerable_time->TimeOver()) invulnerable = false;

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

	App->textures->Unload(texture_sprite);

	RELEASE(state);
	RELEASE(invulnerable_time);
	return true;
}

void ModulePlayer::LoadData()
{
	std::string name;
	info_type info;
	GenericData data;

	texture_sprite = App->textures->Load(IMG_PLAYER);

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

	fx_player_attack = App->audio->LoadFx(FX_PLAYER_ATTACK);
	fx_player_superattack = App->audio->LoadFx(FX_PLAYER_SUPERATTACK);
	fx_charging = App->audio->LoadFx(FX_PLAYER_CHARGING);
	fx_player_hurt = App->audio->LoadFx(FX_PLAYER_HURT);
	fx_player_tired = App->audio->LoadFx(FX_PLAYER_TIRED);
	fx_player_jump = App->audio->LoadFx(FX_PLAYER_JUMP);
	fx_player_land = App->audio->LoadFx(FX_PLAYER_LAND);
	fx_super_jump = App->audio->LoadFx(FX_SUPER_JUMP);
}

void ModulePlayer::OnCollision(Collider* my_collider, Collider* other_collider)
{
	state->OnCollision(my_collider, other_collider);
}

void ModulePlayer::SetArm(ParticleArm* arm)
{
	this->arm = arm;
}

void ModulePlayer::StopArm()
{
	if (arm != nullptr) arm->state = ARM_STOP;
}

// returns the COLLIDER_DETECT_GROUND of the player
// looks in animation and frame colliders
// animation collider has preference
// nullptr if no COLLIDER_DETECT_GROUND found
Collider* ModulePlayer::GetGroundCollider()
{
	for (auto& collider : current_animation->colliders)
		if (collider->type == COLLIDER_DETECT_GROUND) return collider;

	for (auto& frame : current_animation->frames)
		for (auto& collider : frame.colliders)
			if (collider->type == COLLIDER_DETECT_GROUND) return collider;

	LOG ("No COLLIDER_DETECT_GROUND found")
	return (nullptr);
}