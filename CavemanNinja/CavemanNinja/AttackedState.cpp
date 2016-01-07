#include "AttackedState.h"
#include "IdleState.h"
#include "PlayerDefeatedState.h"
#include "Timer.h"

AttackedState::~AttackedState()
{
	delete timer;
}

PlayerState* AttackedState::update(ModulePlayer& player)
{
	switch (substate)
	{
	case MOVE_UP:
		player.position.y -= 1;
		if (player.position.y <= initial_y - 10) substate = MOVE_DOWN;
		break;
	case MOVE_DOWN:
		player.position.y *= 1.02f;
		//if (player.position.y >= initial_y) substate = ON_GROUND;
		break;
	case ON_GROUND:
		//if (timer->TimeOver()) return new IdleState();
		//debug
		if (timer->TimeOver()) // OR energía == 0
		{
			if (attacked_from == ATTACKED_FROM_BEHIND) return new PlayerDefeatedState(ATTACKED_FROM_BEHIND);
			else return new PlayerDefeatedState(ATTACKED_FROM_FRONT);
		}
	}

	if (substate != ON_GROUND)
	{
		player.position.x += move;
		if (ScreenLimitReached(player) == LEFT || ScreenLimitReached(player) == RIGHT) player.position.x -= move;
	}
	return nullptr;
}

void AttackedState::enter(ModulePlayer& player)
{
	timer = new Timer(600);
	timer->StartTimer();
	initial_y = player.position.y;

	player.x_speed = 0;
	player.y_speed = 0;
	
	substate = MOVE_UP;
	if (attacked_from == ATTACKED_FROM_FRONT)
	{
		player.SetCurrentAnimation(&player.frontattack);
		if (player.direction == LEFT) move = +1;
		else move = -1;
	}
	else
	{
		player.SetCurrentAnimation(&player.backattack);
		if (player.direction == LEFT) move = -1;
		else move = +1;
	}
}

void AttackedState::OnCollision(Collider* c1, Collider* c2)
{
	if (substate == MOVE_DOWN)
	{
		ModulePlayer* player = dynamic_cast<ModulePlayer*>(c1->callback);

		if (c2->type == COLLIDER_GROUND || c2->type == COLLIDER_PLATFORM)
		{
			while (c1->IsColliding(c2))
			{
				c1->rect.y -= 1;
				player->position.y -= 1.0f / (float)SCREEN_SIZE;
			}
			substate = ON_GROUND;
		}
	}
}