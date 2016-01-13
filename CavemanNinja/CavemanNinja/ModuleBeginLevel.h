#ifndef __MODULEBEGINLEVEL_H__
#define __MODULEBEGINLEVEL_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"

struct SDL_Texture;
class Timer;

class ModuleBeginLevel : public Module
{
public:
	ModuleBeginLevel() : Module(true) {};

	bool Start();
	update_status Update();
	bool CleanUp();
	void Transition(Module* next_scene, Module* previous_scene = nullptr, Uint32 time = 0);
	void LoadData();

private:
	Timer* timer;
	Animation ready;
	Animation scoretable;
	Animation *current;
	SDL_Texture* texture_transition;
	int center_x;
	int center_y;
	bool transition_running = false;
	Module* next_scene = nullptr;
};

#endif // __MODULEBEGINLEVEL_H__