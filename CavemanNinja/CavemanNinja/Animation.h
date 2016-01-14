#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL_rect.h"
#include "Collider.h"
#include "Globals.h"

#include <vector>
#include <list>

class Module;

using namespace std;

class Animation
{
public:
	Animation();
	Animation(Animation& source, Module* new_callback);
	~Animation();

	FrameInfo& GetCurrentFrame();
	FrameInfo& PeekFrame(int n);
	void SetLastFrame();
	void ClearAnimation();	// mark 'to_destroy' all (frame and animation) colliders 
	bool Finished() const;
	void Reset();
	void SetAlternateVersion(Animation* alternate_version);

	float speed = 1.0f;
	bool loop = true;
	vector<FrameInfo> frames;
	list<Collider*> colliders;
	
	bool alternate;
	float current_frame = 0.0f;

private:
	int loops = 0;
	Animation* alternate_version;
};

#endif // __ANIMATION_H__