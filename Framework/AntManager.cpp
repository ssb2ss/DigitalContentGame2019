#include "stdafx.h"
#include "AntManager.h"
#include "Scene.h"
#include "GameOverScene.h"

AntManager::AntManager()
{

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

void AntManager::Destroy(Ant* a)
{
	destroyed.push_back(a);
}

void AntManager::Update()
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
	for (auto& i : destroyed)
	{
		antList.remove(i);
		currentAntGroup.remove(i);
		Scene::GetCurrentScene().Destroy(i);
	}
	destroyed.clear();
}