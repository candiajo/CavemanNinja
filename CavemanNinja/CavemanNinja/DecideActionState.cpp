#include "DecideActionState.h"
#include "AgressiveAttackState.h"
#include "MoveState.h"
#include "Timer.h"
#include <cstdlib>

DecideActionState::~DecideActionState()
{
	delete timer;
}

// decide next move (slow stone, fast stone, enemy, open mouth only, agressive attack or move
DinoState* DecideActionState::update(ModuleDino& dino)
{
	if (timer->TimeOver())
	{
		timer->StartTimer();
		
		int random_number;
		int destination;
		
		srand(SDL_GetTicks());

		random_number = rand() % 100 + 1;

		if (random_number <= 34) destination = FAR_POSITION;
		else if (random_number <= 67)  destination = MIDDLE_POSITION;
		else destination = NEAR_POSITION;
		
		if (random_number <= 5)	// Move 5%
		{
			return new MoveState(destination);
		}
		else if (random_number <= 10)	// fake shot 5%
		{
			LOG("fake shot");
			return new DecideActionState();
		}
		else if (random_number <= 30 && dino.position.x != NEAR_POSITION)	// agressive atack 20% (if not already in NEAR position)
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
				if (random_number <= 50) return new MoveState(destination, SLOW_STONE);			// 50%
				else if (random_number <= 70) return new MoveState(destination, FAST_STONE);	// 20%
				else return new MoveState(destination, ENEMY);									// 30%
			}
			return new DecideActionState();
		}
	}
	else
	{
		return nullptr;
	}
}

void DecideActionState::enter(ModuleDino& dino)
{
	timer = new Timer(1000);	// only one decisione every second
	timer->StartTimer();
}
