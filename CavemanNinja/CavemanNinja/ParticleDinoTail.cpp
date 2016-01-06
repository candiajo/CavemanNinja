#include "ParticleDinoTail.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

ParticleDinoTail::ParticleDinoTail(particle_type type, Sprite* generator) : Particle(type, generator)
{
	 dinotail = new Animation(App->particles->dinotail_animation, this);

	 position.x = TAIL_LIMIT_LEFT;
	 position.y = TAIL_Y;

	 SetCurrentAnimation(dinotail);

	 state = TAIL_FORWARD;
}

ParticleDinoTail::~ParticleDinoTail()
{
	delete dinotail;
}

void ParticleDinoTail::ParticleUpdate()
{
	switch (state)
	{
	case TAIL_FORWARD:
		position.x += TAIL_SPEED_FORWARD;
		if (position.x >= TAIL_LIMIT_RIGHT)
		{
			position.x = TAIL_LIMIT_RIGHT;
			state = TAIL_BACKWARDS;
		}
		break;
	case TAIL_BACKWARDS:
		position.x -= TAIL_SPEED_BACKWARDS;
		if (position.x <= TAIL_LIMIT_LEFT)
		{
			position.x = TAIL_LIMIT_LEFT;
			state = TAIL_STOP;
		}
		break;
	case TAIL_STOP:
		to_destroy = true;
		break;
	}

	current_frame = &(*current_animation).GetCurrentFrame();
	PlaceColliders();
	App->renderer->Blit(texture_sprite, (int)position.x, (int)position.y, &(*current_frame).section, Flip());
}

void ParticleDinoTail::OnCollision(Collider* c1, Collider* c2)
{}