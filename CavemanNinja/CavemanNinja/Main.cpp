//#include <vld.h> // visual leak detector

#include "Globals.h"
#include "Application.h"
#include "File.h"

Application* App = nullptr;

int main()
{
	int return_state = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	int update_return;
	
	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:
			LOG("...........Creating Application...........");
			App = new Application();
			state = MAIN_INIT;
			break;

		case MAIN_INIT:
			LOG("...........Init Application...........");
			if (App->Init() == false)
			{
				LOG("...........Application Init exits with error...........");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_START;
			}
			break;

		case MAIN_START:
			LOG("...........Application Start...........");
			if (App->Start() == false)
			{
				LOG("...........Application Start exits with error...........");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG("...........Application Update...........");
			}

		case MAIN_UPDATE:
			update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				LOG("...........Application Update exits with error...........");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
			break;

		case MAIN_FINISH:
			LOG("...........Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG("...........Application CleanUp exits with error...........");
			}
			else
			{
				delete App;
				return_state = EXIT_SUCCESS;
			}

			state = MAIN_EXIT;
			break;
		}
	}

	return return_state;
}