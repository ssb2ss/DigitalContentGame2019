#include "stdafx.h"
#include "Enemy.h"
#include "GridManager.h"
#include "TimeManager.h"


Enemy::Enemy(int x, int y) :
	GameObject(L"resources/sprites/ant_ghost.png", Vector2(52 + (x * GRID_SIZE), 56 + (y * GRID_SIZE)))
{
	col = new CircleCollider(*transform, 0.f, 0.f, 60.f);
	attackAvail = false;
	timeCheck = 0.f;
	timeCount = 4.f;
}


Enemy::~Enemy()
{
	SAFE_DELETE(col);
}

void Enemy::Damage()
{
	--hp;
}

void Enemy::AttackAvail()
{
	
	timeCheck += TimeManager::GetDeltaTime();

	if (timeCheck >= timeCount)
	{
		attackAvail = true;
		timeCheck = 0;
		
	}
}