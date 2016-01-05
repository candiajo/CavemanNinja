#ifndef __MODULEBEGINLEVEL_H__
#define __MODULEBEGINLEVEL_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleBeginLevel : public Module
{
public:
	ModuleBeginLevel(bool active) : Module(active) {};
	~ModuleBeginLevel() {};

	bool Start();
	update_status Update();
	void Transition(Module* next_scene, Module* previous_scene = nullptr, Uint32 time = 0);

private:
	SDL_Texture* texture_ready;
	int center_x;
	int center_y;
	bool transition_running = false;
	Uint32 start_time = 0;
	Uint32 total_time = 0;
	Module* next_scene = nullptr;
};

#endif // __MODULEBEGINLEVEL_H__