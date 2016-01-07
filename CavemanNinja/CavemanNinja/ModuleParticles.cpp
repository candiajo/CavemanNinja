#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "File.h"
#include "Particle.h"
#include "ParticleAxe.h"
#include "ParticleStone.h"
#include "ParticleEnemy.h"
#include "ParticleDinoTail.h"
#include "ParticleArm.h"

bool ModuleParticles::Start()
{
	LOG("Loading particles");

	texture_particles = App->textures->Load(IMG_PARTICLES);
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
	case SLOW_STONE: case FAST_STONE:
		particles.push_back(new ParticleStone(type, dynamic_cast<Sprite*>(generator)));
		break;
	case ENEMY:
		particles.push_back(new ParticleEnemy(type, dynamic_cast<Sprite*>(generator)));
		break;
	case DINO_TAIL:
		particles.push_back(new ParticleDinoTail(type, dynamic_cast<Sprite*>(generator)));
		break;
	case ARM:
		particles.push_back(new ParticleArm(type, dynamic_cast<Sprite*>(generator)));
		break;
	}
}

void ModuleParticles::LoadData()
{
	std::string name;
	info_type info;
	GenericData data;

	File player_data(DATA_PARTICLES);

	while (player_data.GetAnimInfo(info, name, data))
	{
		if (name == "axe") StoreData(info, data, axe_animation, this);
		else if (name == "superaxe") StoreData(info, data, superaxe_animation, this);
		else if (name == "rollingstone") StoreData(info, data, rollingstone_animation, this);
		else if (name == "breakingstone") StoreData(info, data, breakingstone_animation, this);
		else if (name == "rollingenemy") StoreData(info, data, rollingenemy_animation, this);
		else if (name == "hitenemy") StoreData(info, data, hitenemy_animation, this);
		else if (name == "dinotail") StoreData(info, data, dinotail_animation, this);
		else if (name == "armslow") 
			StoreData(info, data, armslow, this);
		else if (name == "armfast") 
			StoreData(info, data, armfast, this);
	}
}

bool ModuleParticles::CleanUp()
{
	for (auto& particle : particles)
		delete particle;

	particles.clear();

	axe_animation.DestroyColliders();
	superaxe_animation.DestroyColliders();
	rollingstone_animation.DestroyColliders();
	breakingstone_animation.DestroyColliders();
	rollingenemy_animation.DestroyColliders();
	hitenemy_animation.DestroyColliders();
	dinotail_animation.DestroyColliders();

	return true;
}