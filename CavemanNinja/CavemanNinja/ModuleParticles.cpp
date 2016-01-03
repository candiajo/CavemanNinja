#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "File.h"
#include "Particle.h"
#include "ParticleAxe.h"
#include "ParticleStone.h"

ModuleParticles::ModuleParticles(bool active) : Module(active)
{}

ModuleParticles::~ModuleParticles()
{}

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
	case STONE: case FAST_STONE:
		particles.push_back(new ParticleStone(type, dynamic_cast<Sprite*>(generator)));
		break;
	}
}

void ModuleParticles::LoadData()
{
	std::string name;
	info_type info;
	Generic_data data;

	File player_data(DATA_PARTICLES);

	while (player_data.GetAnimInfo(info, name, data))
	{
		if (name == "axe") 
			StoreData(info, data, axe_animation, this);
		else if (name == "superaxe") StoreData(info, data, superaxe_animation, this);
		else if (name == "rollingstone") StoreData(info, data, rollingstone_animation, this);
		else if (name == "breakingstone") StoreData(info, data, breakingstone_animation, this);
		else if (name == "rollingenemy") StoreData(info, data, rollingenemy_animation, this);
		else if (name == "hitenemy") StoreData(info, data, hitenemy_animation, this);
	}
}


