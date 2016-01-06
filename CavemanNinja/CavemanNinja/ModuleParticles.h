#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include <list>

class Particle;

struct SDL_Texture;

class ModuleParticles : public Module
{
public:
	ModuleParticles(bool active) : Module(true) {};
	~ModuleParticles() {};

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void AddParticle(particle_type type, Module* generator);

	Animation axe_animation;
	Animation superaxe_animation;
	Animation rollingstone_animation;
	Animation breakingstone_animation;
	Animation rollingenemy_animation;
	Animation hitenemy_animation;
	Animation dinotail_animation;
	
	SDL_Texture* texture_particles;

private:
	std::list<Particle*> particles;
	void LoadData();

};

#endif //__MODULEPARTICLES_H__