#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "File.h"
#include "Particle.h"
#include "ParticleAxe.h"
#include "ParticleWheel.h"
#include "ParticleStone.h"
#include "ParticleEnemy.h"
#include "ParticleDinoTail.h"
#include "ParticleArm.h"
#include "ParticleHit.h"
#include "ParticleItem.h"
#include "ParticleBone.h"
#include "ParticleTusk.h"

bool ModuleParticles::Start()
{
	LoadData();
	return true;
}

update_status ModuleParticles::Update()
{
	for (auto& particle : particles)
		particle->ParticleUpdate();

	return UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
{
	for (auto it = particles.begin(); it != particles.end();)
	{
		if ((*it)->to_destroy)
		{
			RELEASE(*it);
			it = particles.erase(it);
		}
		else
			++it;
	}
	
	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(particle_type type, Module* generator)
{
	switch (type)
	{
	case AXE_HORZ: case AXE_VERT: case SUPER_AXE: case AXE_CROUCH:
		particles.push_back(new ParticleAxe(type, dynamic_cast<Sprite*>(generator)));
		break;
	case BONE_HORZ: case BONE_VERT: case SUPER_BONE: case BONE_CROUCH:
		particles.push_back(new ParticleBone(type, dynamic_cast<Sprite*>(generator)));
		break;
	case WHEEL_HORZ: case WHEEL_VERT: case SUPER_WHEEL: case WHEEL_CROUCH:
		particles.push_back(new ParticleWheel(type, dynamic_cast<Sprite*>(generator)));
		break;
	case TUSK_HORZ: case TUSK_VERT: case TUSK_CROUCH: case SUPER_TUSK:
		particles.push_back(new ParticleTusk(type, dynamic_cast<Sprite*>(generator)));
		break;
	case SLOW_STONE: case FAST_STONE:
		particles.push_back(new ParticleStone(type, dynamic_cast<Sprite*>(generator)));
		break;
	case ENEMY:
		particles.push_back(new ParticleEnemy(type, dynamic_cast<Sprite*>(generator)));
		break;
	case DINO_TAIL:
		particles.push_back(new ParticleDinoTail(type, dynamic_cast<Sprite*>(generator)));
		break;
	case HIT_PLAYER: case KUP: case WAM_H: case WAM_V: case WOMP: case HIT_DINO:
		particles.push_back(new ParticleHit(type, dynamic_cast<Sprite*>(generator)));
		break;	
	case ITEM_WHEEL: case ITEM_BONE: case ITEM_BOOMERANG: case ITEM_TUSK:
		particles.push_back(new ParticleItem(type));
		break;
	case ARM:
		ParticleArm* arm = new ParticleArm(type, dynamic_cast<Sprite*>(generator));
		particles.push_back(arm);
		App->player1->SetArm(arm);
		arm = nullptr;
		break;

	}
}

void ModuleParticles::LoadData()
{
	std::string name;
	info_type info;
	GenericData data;

	LOG("Loading particles");

	texture_particles = App->textures->Load(IMG_PARTICLES);

	File player_data(DATA_PARTICLES);

	while (player_data.GetAnimInfo(info, name, data))
	{
		if (name == "axe") StoreData(info, data, axe_animation, this);
		else if (name == "superaxe") StoreData(info, data, superaxe_animation, this);
		else if (name == "bone") StoreData(info, data, bone_animation, this);
		else if (name == "superbone") StoreData(info, data, superbone_animation, this);
		else if (name == "wheel") StoreData(info, data, wheel_animation, this);
		else if (name == "tusk") StoreData(info, data, tusk_animation, this);
		else if (name == "superwheel") StoreData(info, data, superwheel_animation, this);
		else if (name == "rollingstone") StoreData(info, data, rollingstone_animation, this);
		else if (name == "breakingstone") StoreData(info, data, breakingstone_animation, this);
		else if (name == "rollingenemy") StoreData(info, data, rollingenemy_animation, this);
		else if (name == "hitenemy") StoreData(info, data, hitenemy_animation, this);
		else if (name == "defeatedenemy") StoreData(info, data, defeatedenemy_animation, this);
		else if (name == "dinotail") StoreData(info, data, dinotail_animation, this);
		else if (name == "armslow") StoreData(info, data, armslow_animation, this);
		else if (name == "armfast") StoreData(info, data, armfast_animation, this);
		else if (name == "hit") StoreData(info, data, hit_animation, this);
		else if (name == "item") StoreData(info, data, item_animation, this);
	}
}

bool ModuleParticles::CleanUp()
{
	for (auto& particle : particles)
		delete particle;

	particles.clear();

	axe_animation.DestroyColliders();
	superaxe_animation.DestroyColliders();
	bone_animation.DestroyColliders();
	superbone_animation.DestroyColliders();
	tusk_animation.DestroyColliders();
	wheel_animation.DestroyColliders();
	superwheel_animation.DestroyColliders();
	rollingstone_animation.DestroyColliders();
	breakingstone_animation.DestroyColliders();
	rollingenemy_animation.DestroyColliders();
	dinotail_animation.DestroyColliders();
	item_animation.DestroyColliders();


	return true;
}