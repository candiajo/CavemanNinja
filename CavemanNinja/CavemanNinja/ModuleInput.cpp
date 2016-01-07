#include "ModuleInput.h"

#include "SDL_scancode.h"
#include "SDL.h"

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

	return ret;
}

update_status ModuleInput::PreUpdate()
{
	static SDL_Event event;

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
	//debug
	debug();
	return UPDATE_CONTINUE;
}

bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);

	return true;
}

key_state ModuleInput::GetKey(int key) const
{
	return keyboard[key];
}

void ModuleInput::debug()
{
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) App->var1 = 0;

	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) App->var1 = 0;
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_UP) App->var1 = 100;
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) App->var2 -= 1;
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) App->var1 += 5;
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) App->var1 -= 5;
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) App->var1 += 1;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) App->var1 -= 1;
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		LOG("var1: %f \n", App->var1);
		LOG("var2: %f \n", App->var2);
		//LOG("var3: %f \n", App->var3);
	}
}