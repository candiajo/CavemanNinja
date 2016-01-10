#ifndef __MODULEHUD_H__
#define __MODULEHUD_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"

struct SDL_Texture;
class Timer;

enum hud_index
{
	NUMBER_0 = 0,
	NUMBER_1,
	NUMBER_2,
	NUMBER_3,
	NUMBER_4,
	NUMBER_5,
	NUMBER_6,
	NUMBER_7,
	NUMBER_8,
	NUMBER_9,
	HISCORE,
	HITDOT,
	JOE_NORMAL,
	JOE_HIT,
	JOE_DEAD,
	VOID_LIFEDOT,
	GREEN_LIFEDOT,
	YELLOW_LIFEDOT,
	ORANGE_LIFEDOT,
	RED_LIFEDOT,
	DINO_LIFEDOT,
	LIVES_0,
	LIVES_1,
	LIVES_2,
	PRESS_START
};


class ModuleHud: public Module
{
public:
	ModuleHud(bool active) : Module(active) {};
	~ModuleHud();

	bool Start();
	update_status Update();
	bool CleanUp();

	void DrawHudItem(hud_index item);

	SDL_Texture* texture_hud = nullptr;

private:
	void LoadData();
	void DrawPlayerLife(int energy);
	void DrawDinoHits(int energy);
	void DrawDinoEnergy(int energy);
	void DrawScore(int score);

	Animation hud;

	Timer* timer;
};

#endif //__MODULEHUD_H__