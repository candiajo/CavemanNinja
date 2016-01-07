#include "TiredState.h"
#include "Timer.h"
#include "IdleState.h"

TiredState::~TiredState()
{
	delete timer;
}

PlayerState* TiredState::update(ModulePlayer& player)
{
	if (timer->TimeOver())
	{
		player.is_tired = false;
		return new IdleState();
	}
	player.y_speed *= 1.08f;
	return SAME_STATE;
}

void TiredState::enter(ModulePlayer& player)
{
	player.SetCurrentAnimation(&player.tired);
	timer = new Timer(2000);
	timer->StartTimer();
	if (player.y_speed < 0.45) player.y_speed = 0.45f;

	this->player = &player;
}

void TiredState::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_GROUND || c2->type == COLLIDER_PLATFORM)
	{
		player->y_speed = 0.0f;

		while (c1->IsColliding(c2))
		{
			c1->rect.y -= 1;
			player->position.y -= 1.0f / (float)SCREEN_SIZE;
		}
	}
};