#include "Animation.h"
#include "Collider.h"


Animation::Animation() : 
frames(), 
speed(1.0f), 
current_frame(0.0f), 
alternate(false), 
alternate_version(nullptr)
{}

Animation::Animation(Animation& source, Module* new_callback)
{
	speed = source.speed;
	loop = source.loop;
	current_frame = source.current_frame;
	loops = source.loops;
	alternate = false;

	// copy animation colliders list
	for (auto& source_collider : source.colliders)
	{
		colliders.push_back(new Collider(*source_collider));
		colliders.back()->callback = new_callback;
	}

	// copy frames list
	for (auto& source_frame : source.frames)
	{
		FrameInfo destination_frame;

		destination_frame.original = source_frame.original;
		destination_frame.alternate= source_frame.alternate;
		destination_frame.section = &(source_frame.original);
		destination_frame.offset = source_frame.offset;

		// copy frame collider list
		for (auto& source_frame_collider : source_frame.colliders)
		{
			destination_frame.colliders.push_back(new Collider(*source_frame_collider));
			destination_frame.colliders.back()->callback = new_callback;
		}

		frames.push_back(destination_frame);
	}
}

Animation::~Animation()
{
	ClearAnimation(); // mark all (frame and animation) colliders to_destroy

	colliders.clear();
	frames.clear();
}

FrameInfo& Animation::GetCurrentFrame()
{
	current_frame += speed;
	if (current_frame >= frames.size())
	{
		if (loop)
			current_frame = 0.0f;
		else
			current_frame = (float)frames.size() - 1;

		loops++;
	}
	if (alternate && alternate_version != nullptr)
		frames[(int)current_frame].section = &frames[(int)current_frame].alternate;
	else
		frames[(int)current_frame].section = &frames[(int)current_frame].original;

	return frames[(int)current_frame];
}

FrameInfo& Animation::PeekFrame(int n)
{
	if (alternate && alternate_version != nullptr)
		frames[n].section = &frames[n].alternate;
	else
		frames[n].section = &frames[n].original;

	if (n > frames.size() - 1)
		return frames[0];		// frame n doesn't exists
	else
		return frames[n];		// frame demanded
}

void Animation::SetLastFrame()
{
	current_frame = (float)frames.size() - 1;
}

bool Animation::Finished() const
{
	return loops > 0;
}

void Animation::Reset()
{
	current_frame = 0;
	loops = 0;
}

// marks to_destroy the colliders in the game colliders list
// deletes from memory all colliders that are not in that list
// deletes all frames
void Animation::ClearAnimation()
{
	// animation colliders
	for (auto& collider : colliders)
	{
		if (collider->OnList) collider->to_destroy = true;
		else RELEASE(collider);
	}

	// colliders in all frames
	for (auto& frame : frames)
		for (auto& collider : frame.colliders)
		{
			if (collider->OnList) collider->to_destroy = true;
			else RELEASE(collider);
		}

	colliders.clear();
	frames.clear();
}

void Animation::SetAlternateVersion(Animation* alternate_version)
{
	for (int i = 0; i < frames.size(); i++)
		frames[i].alternate = alternate_version->frames[i].original;

	this->alternate_version = alternate_version;
}
