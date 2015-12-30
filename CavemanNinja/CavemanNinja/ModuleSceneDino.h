#ifndef __MODULESCENEDINO_H__
#define __MODULESCENEDINO_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneDino : public Module
{
public:
	ModuleSceneDino(bool start_enabled = true);
	~ModuleSceneDino();

	bool Start();
	update_status Update();
	bool CleanUp();

	SDL_Texture* texture_title = nullptr;
};

#endif //__MODULESCENEDINO_H__