#ifndef __MODULESCENEDINO_H__
#define __MODULESCENEDINO_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"

class Timer;
struct SDL_Texture;

enum scene_state
{
	PLAY,
	GAMEOVER,
	PRE_CONGRATULATIONS,
	CONGRATULATIONS
};

class ModuleSceneDino : public Module
{
public:
	ModuleSceneDino(bool active) : Module(active) {};
	~ModuleSceneDino(){};

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void NextScene(Module* scene);
	void DrawScenario();

	bool dino_defeated;
	//debug bool player_defeated = false;
	SDL_Texture* texture_scene_dino = nullptr;

private:
	void LoadData();
	Animation bgvolcanos;
	Animation bgflowers;
	Animation bgplatform;
	Animation girl;
	Animation gameover;
	Animation congratulations;
	scene_state state;

	Timer* timer;
};

#endif //__MODULESCENEDINO_H__