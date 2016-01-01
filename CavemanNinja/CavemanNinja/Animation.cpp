#include "Animation.h"

Animation::Animation() : frames(), speed(1.0f), current_frame(0.0f)
{}

Animation::~Animation()
{}

Frame_info& Animation::GetCurrentFrame()
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
				current_frame = frames.size() - 1;

			loops++;
		}
		return frames[(int)current_frame];
	}
}

// TODO ¿lo necesito?
/*
const Frame_info& Animation::PeekCurrentFrame() const
{
	return frames[(int)current_frame];
}
*/

bool Animation::Finished()
{
	return loops > 0;
}

void Animation::Reset()
{
	current_frame = 0;
	loops = 0;
}