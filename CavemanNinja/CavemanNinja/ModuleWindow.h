#ifndef __MODULEWINDOW_H__
#define __MODULEWINDOW_H__

#include "Module.h"

struct SDL_Window;
struct SDL_Surface;

class ModuleWindow : public Module
{
public:
	ModuleWindow() : Module(true) {};

	bool Init();
	bool CleanUp();

public:
	SDL_Window* window = nullptr;
	SDL_Surface* screen_surface = nullptr;
};


#endif // __MODULEWINDOW_H__
