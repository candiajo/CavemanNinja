#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Module.h"
#include "SDL.h"

class PlayerState;
class Timer;


class Sprite : public Module
{
public:
	Sprite();
	Sprite(bool active);

	void SetCurrentAnimation(Animation* next_animation, bool alternate = false);

	Animation* previous_animation = nullptr;
	Animation* current_animation = nullptr;
	float x_speed = 0;
	float y_speed = 0;
	type_direction direction;
	Point position;
	FrameInfo* previous_frame = nullptr;		// the animation frame rendered in the previous game frame
	FrameInfo* current_frame = nullptr;			// the animation frame rendered in the current game frame
	int energy;

protected:
	SDL_RendererFlip Flip();
	void RefreshColliders();
	void PlaceColliders();

	SDL_Texture* texture_sprite = nullptr;
	Timer* timer = nullptr;
};

#endif //__SPRITE_H__