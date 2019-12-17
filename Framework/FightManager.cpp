#include "stdafx.h"
#include "FightManager.h"



FightManager::FightManager(AntManager* am, EnemyManager* em) :
	antManager(am), enemyManager(em)
{
	atetimeCheck = 0;
	etatimeCheck = 0;
}	


FightManager::~FightManager()
{

}

void FightManager::LateUpdate()
{

	for (auto& a : antManager->antList)
	{
		for (auto& e : enemyManager->enemyList)
		{
			if (a->col->Intersected(*(e->col)))
			{ 
				a->AttackAvail();
				e->AttackAvail();

				if (a->attackAvail)
				{
					AntToEnemy(e);
					a->attackAvail = false;
					std::cout << "d" << std::endl;

				}
				if (e->attackAvail)
				{
					EnemyToAnt(a);
					e->attackAvail = false;
					std::cout << "e" << std::endl;
				}

			}
		}
	}
}

void FightManager::AntToEnemy(Enemy *em)
{
	em->Damage();
	if (em->hp <= 0)
	{
		enemyManager->Destroy(em);
	}
}

void FightManager::EnemyToAnt(Ant *a)
{
	antManager->Destroy(a);
}
