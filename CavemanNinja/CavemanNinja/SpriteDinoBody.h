#ifndef __SPRITEDINOBODY_H__
#define __SPRITEDINOBODY_H__

#include "Sprite.h"
#include "Animation.h"

#define BODY_X_OFFSET -73
#define BODY_Y_OFFSET 16

class ModuleDino;

class SpriteDinoBody : public Sprite
{
public:
	SpriteDinoBody(bool active) : Sprite(active) {};
	SpriteDinoBody(SDL_Texture* sprite_texture);
	~SpriteDinoBody() {};

	bool Start();
	update_status Update(Point head_position);

	void OnCollision(Collider* c1, Collider* c2);

	Animation* dinobody_animation;
	Animation* dinobodyground_animation;

private:
	ModuleDino* dino;
};

#endif // __MODULEDINO_H__