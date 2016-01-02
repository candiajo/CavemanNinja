#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL_rect.h"
#include "Globals.h"

#include <vector>
#include <list>

using namespace std;

class Animation
{
public:
	Animation();
	~Animation();

	Frame_info& GetCurrentFrame();
	const Frame_info& PeekCurrentFrame() const;
	
	bool Finished();
	void Reset();

	float speed = 1.0f;
	bool loop = true;
	vector<Frame_info> frames;
	list<Collider*> colliders;

private:
	float current_frame = 0.0f;
	int loops = 0;
};

#endif // __ANIMATION_H__