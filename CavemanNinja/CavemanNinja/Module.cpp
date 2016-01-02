#include "Module.h"
#include "Animation.h"
#include "Collider.h"

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

void Module::OnCollision(Collider* a, Collider* b)
{}

void Module::StoreData(info_type info, Generic_data& data, Animation& animation, Module* module)
{
	Frame_info frame;
	Point offset;
	int frame_w;

	switch (info)
	{
	case FRAME_INFO:
		frame.section.x = data.val1;
		frame.section.y = data.val2;
		frame.section.w = data.val3;
		frame.section.h = data.val4;
		animation.frames.push_back(frame);
		break;

	case SPEED_INFO:
		animation.speed = data.val5;
		break;

	case LOOP_INFO:
		animation.loop = (data.val1 == 1);
		break;

	case OFFSET_INFO:
		animation.frames.back().x_offset = data.val1;
		animation.frames.back().y_offset = data.val2;
		break;

	case FRAME_COLLIDER:
		offset.x = data.val1 * SCREEN_SIZE;
		offset.y = data.val2 * SCREEN_SIZE;
		data.val3 *= SCREEN_SIZE;
		data.val4 *= SCREEN_SIZE;
		frame_w = animation.frames.back().section.w;
		animation.frames.back().colliders.push_back(new Collider({ 0, 0, data.val3, data.val4 }, offset, frame_w, data.type, module));
		break;

	case ANIMATION_COLLIDER:
		offset.x = data.val1 * SCREEN_SIZE;
		offset.y = data.val2 * SCREEN_SIZE;
		data.val3 *= SCREEN_SIZE;
		data.val4 *= SCREEN_SIZE;
		frame_w = animation.frames.back().section.w;
		animation.colliders.push_back(new Collider({ 0, 0, data.val3, data.val4 }, offset, frame_w, data.type, module));
		break;
	}
}
