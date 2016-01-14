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

class SpritePlatform;

class ModuleSceneDino : public Module
{
public:
	ModuleSceneDino(bool active) : Module(active) {};

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void NextScene(Module* scene);
	void DrawScenario();
	const particle_type GetRandomItem() const;

	bool dino_defeated;
	bool enter_dino;
	bool player_defeated;
	SDL_Texture* texture_scene_dino = nullptr;

	SpritePlatform* bgplatform_sprite;

private:
	void LoadData();
	Animation bgvolcanos;
	Animation bgflowers;
	Animation girl;
	Animation gameover;
	Animation congratulations;
	Animation bgplatform_animation;

	scene_state state;

	Timer* timer;
};

#endif //__MODULESCENEDINO_H__