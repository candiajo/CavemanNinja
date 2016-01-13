#include "Particle.h"
#include "Application.h"
#include "ModuleParticles.h"

Particle::Particle()
{
	texture_sprite = App->particles->texture_particles;
	particle_flag = NORMAL;
}

Particle::Particle(particle_type type) : Particle()
{
	this->type = type;
}

Particle::Particle(particle_type type, Sprite* generator) : Particle()
{
	this->position = generator->position;
	this->direction = generator->direction;
	this->type = type;
}

Particle::~Particle()
{}

