#ifndef __MODULESCENEDINO_H__
#define __MODULESCENEDINO_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleSceneDino : public Module
{
public:
	ModuleSceneDino(bool active) : Module(active) {};
	~ModuleSceneDino(){};

	bool Start();
	update_status Update();
	bool CleanUp();

	SDL_Texture* texture_scene_dino = nullptr;

private:
	void LoadData();
	Animation bgvolcanos;
	Animation bgflowers;
	Animation bgplatform;
	Animation girl;
};

#endif //__MODULESCENEDINO_H__