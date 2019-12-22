#include "stdafx.h"
#include "Enemy.h"
#include "GridManager.h"
#include "TimeManager.h"
#include "GameManager.h"

Enemy::Enemy(int x, int y) :
	GameObject(L"resources/sprites/ant_ghost.png", GameManager::GetInstance()->GetGridPos(x, y)), x(x), y(y)
{
	transform->SetScale(0.5f, 0.5f);

	col = new CircleCollider(*transform, 0.f, 0.f, 60.f);
	attackAvail = false;
	timeCheck = 0.f;
	timeCount = 5.f;

	hp = 5;
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
