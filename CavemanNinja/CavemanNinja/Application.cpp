#include "Application.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneTitle.h"
#include "ModuleSceneDino.h"
#include "ModuleBeginLevel.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"

Application::Application()
{
	modules.push_back(input = new ModuleInput(true));
	modules.push_back(window = new ModuleWindow(true));
	modules.push_back(textures = new ModuleTextures(true));
	modules.push_back(collisions = new ModuleCollisions(true));
	modules.push_back(begin_level = new ModuleBeginLevel(true));

	modules.push_back(scene_title = new ModuleSceneTitle(false));
	modules.push_back(scene_dino = new ModuleSceneDino(true));

	modules.push_back(player1 = new ModulePlayer(true));

	modules.push_back(renderer = new ModuleRender(true));
}

Application::~Application()
{
	for (auto& it : modules) delete(it);
}

bool Application::Init()
{
	bool ret = true;

	for (auto it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	return ret;
}

bool Application::Start()
{
	bool ret = true;

	for (auto it = modules.begin(); it != modules.end() && ret; ++it)
		if ((*it)->IsEnabled()) 
			ret = (*it)->Start();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (auto it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->PreUpdate();

	for (auto it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->Update();

	for (auto it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (auto it = modules.rbegin(); it != modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}