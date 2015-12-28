#include "Application.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

Application::Application()
{
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(renderer = new ModuleRender());
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
		ret = (*it)->PreUpdate();

	for (auto it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update();

	for (auto it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
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