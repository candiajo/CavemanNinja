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
	void SetCurrentAnimation(Animation* next_animation);

	Animation* previous_animation = nullptr;
	Animation* current_animation = nullptr;
	float x_speed = 0;
	float y_speed = 0;
	Direction direction;
	Point position;
	Frame_info* previous_frame = nullptr;		// the animation frame rendered in the previous game frame
	Frame_info* current_frame = nullptr;		// the animation frame rendered in the current game frame

protected:
	SDL_RendererFlip Flip();
	void RefreshColliders();
	void PlaceColliders();

	SDL_Texture* texture_sprite = nullptr;
	PlayerState* state;
	Timer* timer;
};

#endif //__SPRITE_H__