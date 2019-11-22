#include "stdafx.h"
#include "EnemyManager.h"
#include "Scene.h"


EnemyManager::EnemyManager()
{
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
