#include "ModulePlayer.h"
#include "TiredState.h"
#include "Timer.h"
#include "IdleState.h"
#include "ModuleAudio.h"

TiredState::~TiredState()
{
	delete timer;
}

PlayerState* TiredState::Update(ModulePlayer& player)
{
	if (timer->TimeOver())
	{
		player.is_tired = false;
		return new IdleState();
	}
	player.y_speed *= 1.08f;
	return SAME_STATE;
}

void TiredState::Enter(ModulePlayer& player)
{
	player.SetCurrentAnimation(&player.tired);
	timer = new Timer(2000);
	timer->StartTimer();
	if (player.y_speed < 0.45) player.y_speed = 0.45f;

	this->player = &player;
	App->audio->PlayFx(player.fx_player_tired);
}

void TiredState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	if (other_collider->type == COLLIDER_GROUND || other_collider->type == COLLIDER_PLATFORM)
	{
		player->y_speed = 0.0f;

		while (my_collider->IsColliding(other_collider))
		{
			my_collider->rect.y -= 1;
			player->position.y -= 1.0f / (float)SCREEN_SIZE;
		}
	}
};