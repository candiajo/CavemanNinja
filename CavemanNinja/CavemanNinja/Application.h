#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleInput;
class ModuleWindow;
class ModuleTextures;
class ModuleRender;
class ModuleSceneTitle;
class ModuleSceneDino;
class ModuleBeginLevel;
class ModulePlayer;
class ModuleCollisions;
class ModuleParticles;

class Application
{
public:
	Application();
	~Application();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

	ModuleInput* input;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleRender* renderer;
	ModuleSceneTitle* scene_title;
	ModuleSceneDino* scene_dino;
	ModuleBeginLevel* begin_level;
	ModulePlayer* player1;
	ModuleCollisions* collisions;
	ModuleParticles* particles;


	//debug
	float var1 = 3, var2 = 1, var3 = 5;

private:
	std::list<Module*> modules;
};

extern Application* App;

#endif // __APPLICATION_CPP__
