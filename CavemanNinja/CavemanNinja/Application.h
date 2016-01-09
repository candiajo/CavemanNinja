#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include <list>
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
class ModuleDino;
class ModuleAudio;

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
	ModuleDino* dino;
	ModuleAudio* audio;

	//debug
	float var1 = 70, var2 = 100, var3 = 1.05f;

private:
	std::list<Module*> modules;
};

extern Application* App;

#endif // __APPLICATION_CPP__
