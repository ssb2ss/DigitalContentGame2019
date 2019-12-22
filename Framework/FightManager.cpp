#include "stdafx.h"
#include "FightManager.h"
#include "GameManager.h"


FightManager::FightManager() :
	antManager(GameManager::GetInstance()->antManager), enemyManager(GameManager::GetInstance()->enemyManager)
{
	atetimeCheck = 0;
	etatimeCheck = 0;
}	


FightManager::~FightManager()
{

}

void FightManager::LateUpdate()
{

	for (auto& e : enemyManager->enemyList)
	{
		for (auto& a : antManager->antList)
		{
			if (a->col->Intersected(*(e->col)))
			{
				e->AttackAvail();
				e->curState = 0;
				float angle = atan2f(a->transform->position.y - e->transform->position.y, a->transform->position.x - e->transform->position.x);
				float rot = angle * (180 / 3.14f);
				e->transform->SetRotation(rot);

				if (e->attackAvail)
				{
					e->attackMotion = true;
					EnemyToAnt(a);
					e->attackAvail = false;
					std::cout << "e" << std::endl;
				}
			
			}
		}
		for (auto& a : antManager->soldierList)
		{
			if (a->col->Intersected(*(e->col)))
			{
				a->AttackAvail();
				e->AttackAvail();

				float angle1 = atan2f(e->transform->position.y - a->transform->position.y, e->transform->position.x - a->transform->position.x);
				float rot1 = angle1 * (180 / 3.14f);
				a->transform->SetRotation(rot1);

				float angle2 = atan2f(a->transform->position.y - e->transform->position.y, a->transform->position.x - e->transform->position.x);
				float rot2 = angle2 * (180 / 3.14f);
				e->transform->SetRotation(rot2);

				if (a->attackAvail)
				{
					a->attackMotion = true;
					AntToEnemy(e);
					a->attackAvail = false;
					std::cout << "d" << std::endl;

				}
				if (e->attackAvail)
				{
					e->attackMotion = true;
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

void FightManager::EnemyToAnt(SoldierAnt * a)
{
	antManager->Destroy(a);
}
