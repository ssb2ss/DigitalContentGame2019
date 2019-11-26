#include "stdafx.h"
#include "EnemyManager.h"
#include "Scene.h"
#include "DayManager.h"
#include "Enemy.h"
#include "GridManager.h"

//생성 : 어연수

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
		PushBackEnemy(new Enemy(tx, ty));
		daySave = DayManager::dayCount;
		spawnCheck = false;
	}
	
	if (DayManager::dayCount - daySave == 1)
	{
		spawnCheck = true;
	}



	/*if (DayManager::dayCount == 1)
	{

	}	
	else if (DayManager::dayCount == 2)
	{
		int tx = rand() % (X_SIZE - 4) + 2;
		int ty = rand() % (Y_SIZE - 2) + 1;
		PushBackEnemy(new Enemy(tx, ty));
	}
	else if (DayManager::dayCount == 3)
	{
		int tx = rand() % (X_SIZE - 4) + 2;
		int ty = rand() % (Y_SIZE - 2) + 1;
		PushBackEnemy(new Enemy(tx, ty));
	}
	if (DayManager::dayCount == 3)
	{
		int tx = rand() % (X_SIZE - 4) + 2;
		int ty = rand() % (Y_SIZE - 2) + 1;
		PushBackEnemy(new Enemy(tx, ty));
	}
	if (DayManager::dayCount == 4)
	{
		int tx = rand() % (X_SIZE - 4) + 2;
		int ty = rand() % (Y_SIZE - 2) + 1;
		PushBackEnemy(new Enemy(tx, ty));
	}*/


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
