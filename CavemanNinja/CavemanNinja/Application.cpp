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
#include "ModuleParticles.h"
#include "ModuleDino.h"

Application::Application()
{
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(collisions = new ModuleCollisions());
	modules.push_back(begin_level = new ModuleBeginLevel());

	modules.push_back(scene_title = new ModuleSceneTitle(false));
	modules.push_back(scene_dino = new ModuleSceneDino(true));

	modules.push_back(player1 = new ModulePlayer(false));
	modules.push_back(particles = new ModuleParticles(false));
	modules.push_back(dino = new ModuleDino(false));
	modules.push_back(renderer = new ModuleRender());
}

Application::~Application()
{
	for (auto& module : modules) 
		delete(module);
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
		if ((*it)->IsEnabled() && !(*it)->HasStarted())
		{
			ret = (*it)->Start();
			(*it)->started = ret;
		}

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
		if ((*it)->IsEnabled()) ret = (*it)->CleanUp();

	return ret;
}