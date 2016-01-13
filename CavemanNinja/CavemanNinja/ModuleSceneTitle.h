#ifndef __MODULESCENETITLE_H__
#define __MODULESCENETITLE_H__

#include "Module.h"
#include "Globals.h"
#include "Timer.h"

struct SDL_Texture;

class ModuleSceneTitle : public Module
{
public:
	ModuleSceneTitle(bool active) : Module(active){};

	bool Start();
	update_status Update();
	bool CleanUp();

	SDL_Texture* texture_title = nullptr;

private:
	unsigned int fx_begin_play;
};

#endif //__MODULESCENETITLE_H__