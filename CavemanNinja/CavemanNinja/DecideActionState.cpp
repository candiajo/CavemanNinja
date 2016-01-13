#include "DecideActionState.h"
#include "AgressiveAttackState.h"
#include "MoveState.h"
#include "SuperHitState.h"
#include "DinoDefeatedState.h"
#include "Timer.h"

DecideActionState::~DecideActionState()
{
	RELEASE(timer);
}

// decide next move (slow stone, fast stone, enemy, open mouth only, agressive attack or move
DinoState* DecideActionState::Update(ModuleDino& dino)
{
	if (event == DINO_IS_DEFEATED) return new DinoDefeatedState();
	else if (event == DINO_GET_SUPERHIT) return new SuperHitState();
	else if (event == DINO_GET_HIT) dino.CloseEye(1000);

	if (timer->TimeOver())
	{
		timer->StartTimer();
		
		if (dino.player_too_near) return new MoveState(VERY_FAR_POSITION, DINO_TAIL);

		int random_number = random_number = rand() % 100 + 1;
		const int destination = GetRandomPosition();
		
		if (random_number <= 5)	// Move 5%
		{
			return new MoveState(destination);
		}
		else if (random_number <= 8)	// fake shot 3%
		{
			return new MoveState(destination, FAKE_ATTACK);
		}
		else if (random_number <= 30 && dino.position.x != NEAR_POSITION)	// agressive atack 22% (if not already in NEAR position)
		{
			return new AgressiveAttackState();
		}
		else // shot rock or enemy 70%
		{
			random_number = rand() % 100 + 1;
			if (dino.position.x == NEAR_POSITION)
			{
				if (random_number <= 20) return new MoveState(destination, SLOW_STONE);			// 20%
				else if (random_number <= 70) return new MoveState(destination, FAST_STONE);	// 50%
				else return new MoveState(destination, ENEMY);									// 30%
			}
			else
			{
				if (random_number <= 60) return new MoveState(destination, SLOW_STONE);			// 60%
				else if (random_number <= 70) return new MoveState(destination, FAST_STONE);	// 10%
				else return new MoveState(destination, ENEMY);									// 30%
			}
			return new DecideActionState();
		}
	}
	else
	{
		return SAME_STATE;
	}
}

void DecideActionState::Enter(ModuleDino& dino)
{
	timer = new Timer(1000);	// only one decisione every second
	timer->StartTimer();
}

void DecideActionState::OnCollision(Collider* my_collider, Collider* other_collider)
{
	DinoState::OnCollision(my_collider, other_collider);
}