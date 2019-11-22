#pragma once
#include "GameObject.h"
#include "AntManager.h"
#include "EnemyManager.h"

class FightManager :
	public GameObject
{
	AntManager* antManager;
	EnemyManager* enemyManager;

	float atetimeCheck;
	float etatimeCheck;
public:
	FightManager(AntManager* am, EnemyManager* em);
	~FightManager();

	virtual void LateUpdate();

	void AntToEnemy(Enemy *em);
	void EnemyToAnt(Ant *a);


};

	