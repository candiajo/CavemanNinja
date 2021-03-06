#include "ModuleInput.h"

#include "SDL_scancode.h"
#include "SDL.h"
#include "Timer.h"

//debug
#include "Application.h"

#pragma comment( lib, "SDL2.lib" )
#pragma comment( lib, "SDL2main.lib" )

ModuleInput::ModuleInput() : Module(true)
{
	keyboard.fill(KEY_IDLE);
}

bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	input_active = true;
	timer = new Timer();

	return ret;
}

update_status ModuleInput::PreUpdate()
{
	static SDL_Event event;

	if (!input_active && timer->TimeOver()) input_active = true;

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == PRESSED)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else //if (keys[i] == KEY_NOT_PRESSED)
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	while (SDL_PollEvent(&event))
	{
		// check of ESC key ------------------------------------------------------------------------

		if (keyboard[SDL_SCANCODE_ESCAPE])
		{
			return UPDATE_STOP;
		}

		// check for closing window by pressing X with the mouse -----------------------------------

		if (event.type == SDL_QUIT) return UPDATE_STOP;
	}

	return UPDATE_CONTINUE;
}

bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);

	RELEASE(timer);

	return true;
}

key_state ModuleInput::GetKey(int key) const
{
	if (input_active) return keyboard[key];
	else return KEY_UP;
}

void ModuleInput::DeactivateInput(int time)
{
	input_active = false;

	timer->StartTimer(time);
}