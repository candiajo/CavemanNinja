#ifndef __SPRITEPLATFORM_H__
#define __SPRITEPLATFORM_H__

#include "Sprite.h"
#include "Animation.h"

#define OFFSET_BY_HIT 13.57f

class SpritePlatform : public Sprite
{
public:
	SpritePlatform() : Sprite(true) {};
	SpritePlatform(SDL_Texture* sprite_texture, Animation* animation);
	~SpritePlatform();

	bool Start();
	update_status Update(int dino_energy);

	void OnCollision(Collider* my_collider, Collider* other_collider) {};

private:
	Animation* bgplatform_animation;
	float y_original;
};

#endif // __SPRITEPLATFORM_H__