#ifndef __SPRITEDINOBODY_H__
#define __SPRITEDINOBODY_H__

#include "Sprite.h"
#include "Animation.h"

class ModuleDino;

class SpriteDinoBody : public Sprite
{
public:
	SpriteDinoBody() : Sprite(true) {};
	SpriteDinoBody(SDL_Texture* sprite_texture);
	~SpriteDinoBody();

	bool Start();
	update_status Update(Point head_position);

	void OnCollision(Collider* my_collider, Collider* other_collider);

	Animation* dinobody_animation;
	Animation* dinobodyground_animation;

private:
	ModuleDino* dino;
};

#endif // __MODULEDINO_H__