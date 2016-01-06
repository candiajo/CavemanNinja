#include "Animation.h"
#include "Collider.h"


Animation::Animation() : frames(), speed(1.0f), current_frame(0.0f)
{}

Animation::Animation(Animation& source, Module* new_callback)
{
	speed = source.speed;
	loop = source.loop;
	current_frame = source.current_frame;
	loops = source.loops;

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

		destination_frame.section = source_frame.section;
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
	DestroyColliders(); // mark all (frame and animation) colliders to_destroy

	colliders.clear();
	frames.clear();
}

FrameInfo& Animation::GetCurrentFrame()
{
	if (frames.size() == 1)
		return frames[0];
	else
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
		return frames[(int)current_frame];
	}
}

FrameInfo& Animation::PeekFrame(int n)
{
	if (n > frames.size() - 1)
		return frames[0];		// frame n doesn't exists
	else
		return frames[n];		// frame demanded
}

void Animation::SetLastFrame()
{
	current_frame = (float)frames.size() - 1;
}

bool Animation::Finished()
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
void Animation::DestroyColliders()
{
	// animation colliders
	for (auto& collider : colliders)
	{
		if (collider->OnList) collider->to_destroy = true;
		else delete collider;
	}

	// colliders in all frames
	for (auto& frame : frames)
		for (auto& collider : frame.colliders)
		{
			if (collider->OnList) collider->to_destroy = true;
			else delete collider;
		}

	colliders.clear();
	frames.clear();
}