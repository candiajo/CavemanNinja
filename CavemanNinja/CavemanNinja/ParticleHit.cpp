#include "Timer.h"
#include "ParticleHit.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

ParticleHit::ParticleHit(particle_type type, Sprite* generator) : Particle(type, generator)
{
	hit = new Animation(App->particles->hit_animation, this);
	SetCurrentAnimation(hit);

	current_frame = &hit->PeekFrame(type);

	position.x = generator->position.x + current_frame->offset.x;
	position.y = generator->position.y + current_frame->offset.y;

	timer = new Timer();

	if (type = WOMP) timer->StartTimer(500);
	else timer->StartTimer(250);
}

ParticleHit::~ParticleHit()
{
	RELEASE(hit);
	RELEASE(timer);
}

void ParticleHit::ParticleUpdate()
{
	if (timer->TimeOver()) to_destroy = true;
	else App->renderer->Blit(texture_sprite, (int)position.x, (int)position.y, current_frame->section, SDL_FLIP_NONE);
}