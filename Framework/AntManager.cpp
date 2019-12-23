#include "stdafx.h"
#include "AntManager.h"
#include "Scene.h"
#include "GameOverScene.h"
#include "TimeManager.h"


AntManager::AntManager()
{
	timeCount = 0;
}

AntManager::~AntManager()
{

}

Ant* AntManager::PushBackAnt(Ant* a)
{
	Scene::GetCurrentScene().PushBackGameObject(a);
	a->renderer->SetLayer(1);
	antList.push_back(a);
	return a;
}

SoldierAnt * AntManager::PushBackAnt(SoldierAnt * a)
{
	Scene::GetCurrentScene().PushBackGameObject(a);
	a->renderer->SetLayer(1);
	soldierList.push_back(a);
	return a;
}

void AntManager::Destroy(Ant* a)
{
	destroyedAnt.push_back(a);
}

void AntManager::Destroy(SoldierAnt * a)
{
	destroyedSoldier.push_back(a);
}

void AntManager::Update()
{
	timeCount += TimeManager::GetDeltaTime();
	if (timeCount >= 0.1f)
	{
		for (auto& i : antList)
		{
			if (!i->isStop && GridManager::grid[i->destX][i->destY] != Grid::EMPTY && GridManager::grid[i->destX][i->destY] != Grid::WATER && GridManager::grid[i->destX][i->destY] != Grid::BUSH)
			{
				i->ResetDest();
			}

			for (auto& j : antList)
			{
				if (i != j && i->isStop && j->isStop && i->x == j->x && i->y == j->y)
				{
					j->ResetDest();
				}
			}
			for (auto& j : soldierList)
			{
				if (i->isStop && j->isStop && i->x == j->x && i->y == j->y)
				{
					j->ResetDest();
				}
			}
		}

		for (auto& i : soldierList)
		{
			if (!i->isStop && GridManager::grid[i->destX][i->destY] != Grid::EMPTY && GridManager::grid[i->destX][i->destY] != Grid::WATER && GridManager::grid[i->destX][i->destY] != Grid::BUSH)
			{
				i->ResetDest();
			}

			for (auto& j : soldierList)
			{
				if (i != j && i->isStop && j->isStop && i->x == j->x && i->y == j->y)
				{
					j->ResetDest();
				}
			}
		}
		timeCount = 0;
	}
}

void AntManager::LateUpdate()
{
	Remove();

	if (antList.empty())
		Scene::ChangeScene(new GameOverScene());
}

void AntManager::Remove()
{
	for (auto& i : destroyedAnt)
	{
		antList.remove(i);
		currentAntGroup.remove(i);
		Scene::GetCurrentScene().Destroy(i);
	}
	for (auto& i : destroyedSoldier)
	{
		soldierList.remove(i);
		Scene::GetCurrentScene().Destroy(i);
	}
	destroyedAnt.clear();
	destroyedSoldier.clear();
}