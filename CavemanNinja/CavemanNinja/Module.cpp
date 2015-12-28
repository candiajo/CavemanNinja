#include "Module.h"

Module::Module()
{}

Module::Module(bool active = true) : active(active)
{}

Module::~Module()
{}

bool Module::IsEnabled() const
{
	return active;
}

bool Module::Enable()
{
	if (active == false)
		return active = Start();

	return true;
}

bool Module::Disable()
{
	if (active == true)
		return active = !CleanUp();

	return true;
}

bool Module::Init()
{
	return true;
}

bool Module::Start()
{
	return true;
}

update_status Module::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status Module::Update()
{
	return UPDATE_CONTINUE;
}

update_status Module::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool Module::CleanUp()
{
	return true;
}