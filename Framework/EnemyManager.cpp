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

void EnemyManager::LateUpdate()
{
	Remove();
}

void EnemyManager::GenerateEnemy(int state)
{
	bool isEmpty = false;
	int x, y;
	while (!isEmpty)
	{
		isEmpty = true;
		x = rand() % (X_SIZE - 4) + 2;
		y = rand() % (Y_SIZE - 2) + 1;

		for (int i = x - 2; i <= x + 2; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				if (GridManager::grid[i][j] != Grid::EMPTY)
				{
					isEmpty = false;
					break;
				}
			}
		}
	}

	PushBackEnemy(new Enemy(x, y, state));
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
