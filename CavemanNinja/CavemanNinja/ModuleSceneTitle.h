#ifndef __MODULESCENETITLE_H__
#define __MODULESCENETITLE_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneTitle : public Module
{
public:
	ModuleSceneTitle(bool start_enabled = true);
	~ModuleSceneTitle();

	bool Start();
	update_status Update();
	bool CleanUp();

	SDL_Texture* texture_title = nullptr;
};

#endif //__MODULESCENETITLE_H__