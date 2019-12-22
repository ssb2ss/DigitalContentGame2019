#include "stdafx.h"
#include "EnemyManager.h"
#include "Scene.h"
#include "DayManager.h"
#include "Enemy.h"
#include "GridManager.h"


EnemyManager::EnemyManager()
{
	daySave = DayManager::dayCount;
	spawnCheck = true;
}


EnemyManager::~EnemyManager()
{
}

Enemy * EnemyManager::PushBackEnemy(Enemy * e)
{
	Scene::GetCurrentScene().PushBackGameObject(e);
	enemyList.push_back(e);
	return e;
}

void EnemyManager::Destroy(Enemy * e)
{
	destroyed.push_back(e);
}

void EnemyManager::Update()
{
	if (spawnCheck)
	{
		int tx = rand() % (X_SIZE - 4) + 2;
		int ty = rand() % (Y_SIZE - 2) + 1;
		while (GridManager::grid[tx][ty] != EMPTY ||
			GridManager::grid[tx + 1][ty] != EMPTY ||
			GridManager::grid[tx - 1][ty] != EMPTY ||
			GridManager::grid[tx][ty + 1] != EMPTY ||
			GridManager::grid[tx][ty - 1] != EMPTY ||
			GridManager::grid[tx + 1][ty + 1] != EMPTY ||
			GridManager::grid[tx + 1][ty - 1] != EMPTY ||
			GridManager::grid[tx - 1][ty + 1] != EMPTY ||
			GridManager::grid[tx - 1][ty - 1] != EMPTY)
		{
			tx = rand() % (X_SIZE - 4) + 2;
			ty = rand() % (Y_SIZE - 2) + 1;
		}
		Enemy* e = PushBackEnemy(new Enemy(tx, ty));
		e->SetSprite(rand() % 2);
		daySave = DayManager::dayCount;
		spawnCheck = false;
	}
	
	if (DayManager::dayCount - daySave == 1)
	{
		spawnCheck = true;
	}

}

void EnemyManager::LateUpdate()
{
	Remove();
}

void EnemyManager::Remove()
{
	for (auto& i : destroyed)
	{
		enemyList.remove(i);
		Scene::GetCurrentScene().Destroy(i);
	}
	destroyed.clear();
}
