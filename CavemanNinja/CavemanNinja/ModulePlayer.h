#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;
class PlayerState;

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	Animation* current_animation = nullptr;
	Animation idle;
	Animation walk;
	Animation crouch;
	Animation lookup;
	float x_speed = 0;
	float y_speed = 0;
private:
	void LoadData();
	SDL_Texture* texture_player = nullptr;
	PlayerState* state;
	Point position;
};

#endif // __MODULEPLAYER_H__