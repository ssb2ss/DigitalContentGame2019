#include "stdafx.h"
#include "Enemy.h"
#include "GridManager.h"
#include "TimeManager.h"
#include "GameManager.h"

Enemy::Enemy(int x, int y) :
	GameObject(L"resources/sprites/ant_ghost.png", GameManager::GetInstance()->GetGridPos(x, y)), x(x), y(y)
{
	transform->SetScale(0.5f, 0.5f);

	col = new CircleCollider(*transform, 0.f, 0.f, 120.f);
	attackAvail = false;
	timeCheck = 0.f;
	timeCount = 5.f;
	motionTimer = 0.f;
	attackMotion = false;

	hp = 5;
}


Enemy::~Enemy()
{
	SAFE_DELETE(col);
}

void Enemy::Update()
{
	if (attackMotion)
		AttackMotion();
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

void Enemy::AttackMotion()
{
	motionTimer += TimeManager::GetDeltaTime();

	float rot = transform->rotatingAngle / (180 / 3.14f);

	if (motionTimer <= 0.1f)
	{
		transform->position.x += cosf(rot) * 500.f * TimeManager::GetDeltaTime();
		transform->position.y += sinf(rot) * 500.f * TimeManager::GetDeltaTime();
	}
	else if (motionTimer <= 0.2f)
	{
		transform->position.x -= cosf(rot) * 500.f * TimeManager::GetDeltaTime();
		transform->position.y -= sinf(rot) * 500.f * TimeManager::GetDeltaTime();
	}
	else
	{
		motionTimer = 0;
		attackMotion = false;
		transform->SetPosition(GameManager::GetInstance()->GetGridPos(x, y));
	}
}
