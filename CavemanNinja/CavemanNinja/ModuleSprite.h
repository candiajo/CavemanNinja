#include "Module.h"
#include "SDL.h"

class PlayerState;

class ModuleSprite : public Module
{
public:
	ModuleSprite::ModuleSprite(bool active);
	void SetCurrentAnimation(Animation* next_animation);

	Animation* previous_animation = nullptr;
	Animation* current_animation = nullptr;
	float x_speed = 0;
	float y_speed = 0;
	Direction direction;
	Point position;

protected:
	SDL_RendererFlip Flip();
	void RefreshColliders();
	void PlaceColliders();

	SDL_Texture* texture_player = nullptr;
	PlayerState* state;
	Frame_info* previous_frame = nullptr;		// the animation frame rendered in the previous game frame
	Frame_info* current_frame = nullptr;		// the animation frame rendered in the current game frame
};