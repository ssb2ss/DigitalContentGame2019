#include "stdafx.h"
#include "Enemy.h"
#include "GridManager.h"
#include "TimeManager.h"
#include "GameManager.h"
#include <time.h>
#include <cstdlib>

Enemy::Enemy(int x, int y) :
	GameObject(L"resources/sprites/ant_ghost.png", GameManager::GetInstance()->GetGridPos(x, y)), x(x), y(y), am(GameManager::GetInstance()->antManager)
{
	transform->SetScale(0.5f, 0.5f);
	
	col = new CircleCollider(*transform, 0.f, 0.f, 120.f);
	attackAvail = false;
	timeCheck = 0.f;
	timeCount = 5.f;
	motionTimer = 0.f;
	attackMotion = false;
	isEnd = true;
	moveList.clear();
	moveCheck = true;
	saveTime = 0;
	moveSpeed = 50;
	hp = 5;

	curState = 1;
	srand(time(NULL));
	
	grid = new GridManager();
}


Enemy::~Enemy()
{
	SAFE_DELETE(col);
}

void Enemy::Update()
{
	if (attackMotion)
		AttackMotion();

	if (!isStop)
	{
		setDest();
		RandomMove();
	}
	else if (isStop)
	{
		Idle();
		transform->SetPosition(GameManager::GetInstance()->GetGridPos(x, y));
	}
	
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
		curState = 2;
		timeCheck = 0;

	}
}

void Enemy::setDest()
{
	if (moveCheck)
	{
		isEnd = true;
		destX = rand() % 239;
		destY = rand() % 134;

		while (GridManager::grid[destX][destY] == Grid::OBSTACLE)
		{
			destX = rand() % 239;
			destY = rand() % 134;
		}
		moveList.clear();
		moveList = grid->SetDest(x, y, destX, destY);
		std::cout << "E" << std::endl;
	}
	moveCheck = false;
	if (!moveList.empty())
	{
		isEnd = false;
	}

}


void Enemy::RandomMove()
{

		Vector2 tempDest = GameManager::GetInstance()->GetGridPos(moveList.front().x, moveList.front().y);
		
		float angle = atan2f(tempDest.y - transform->position.y, tempDest.x - transform->position.x);
		float rot = angle * (180 / 3.1415921648);
		float rotRate = (rot - transform->rotatingAngle) / 2.f;

		if (TimeManager::GetDeltaTime() < 0.1f)
		{
			transform->SetRotation(rot);
			transform->position.x += cosf(angle) * moveSpeed * TimeManager::GetDeltaTime();
			transform->position.y += sinf(angle) * moveSpeed * TimeManager::GetDeltaTime();
		}
			if (col->Intersected(Vector2(tempDest.x, tempDest.y)))
			{
				x = moveList.front().x;
				y = moveList.front().y;
				moveList.erase(moveList.begin());
				if (moveList.empty())
				{
					destX = x;
					destY = y;
					if (GridManager::grid[x][y] == Grid::EMPTY)
						GridManager::grid[x][y] = Grid::OBSTACLE;
					transform->SetPosition(GameManager::GetInstance()->GetGridPos(x, y));

					isStop = true;
				}
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


void Enemy::Idle()
{
	saveTime += TimeManager::GetDeltaTime();
	if (saveTime >= 3)
	{
		isStop = false;
		moveCheck = true;
		saveTime = 0;
	}
}