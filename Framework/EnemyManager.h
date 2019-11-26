#pragma once
#include "GameObject.h"
#include "Enemy.h"

class EnemyManager :
	public GameObject
{
public:
	EnemyManager();
	~EnemyManager();

	std::list<Enemy*> enemyList;

	Enemy* PushBackEnemy(Enemy* e);
	void Destroy(Enemy* e);
	virtual void Update();
	virtual void LateUpdate();

	int daySave;
	bool spawnCheck;
private:
	std::list<Enemy*> destroyed;
	void Remove();
};

