#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleInput;
class ModuleWindow;
class ModuleTextures;
class ModuleRender;

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

private:
	std::list<Module*> modules;
};

extern Application* App;

#endif // __APPLICATION_CPP__
