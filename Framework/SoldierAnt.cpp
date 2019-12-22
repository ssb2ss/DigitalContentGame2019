#include "stdafx.h"
#include "SoldierAnt.h"
#include "GameManager.h"

#define PI 3.1415926535f

SoldierAnt::SoldierAnt(int x, int y) :
	GameObject(L"resources/sprites/ant_soldier.png", GameManager::GetInstance()->GetGridPos(x, y)), moveSpeed(200.f),
	x(x), y(y), destX(x), destY(y), isStop(true)
{
	transform->SetScale(0.4f, 0.4f);
	col = new CircleCollider(*transform, 2.f);
	gridManager = new GridManager();
	moveList.clear();
	GridManager::grid[x][y] = Grid::OBSTACLE;

	curCameraPos = GameManager::GetInstance()->cameraPos;

	attackAvail = false;
	attackMotion = false;
	motionTimer = 0;
	timeCheck = 0.f;
	timeCount = 3.f;
}

SoldierAnt::~SoldierAnt()
{
	SAFE_DELETE(col);
	SAFE_DELETE(gridManager);
}

void SoldierAnt::Update()
{
	if (!isStop)
	{
		Vector2 tempDest = GameManager::GetInstance()->GetGridPos(moveList.front().x, moveList.front().y);

		float angle = atan2f(tempDest.y - transform->position.y, tempDest.x - transform->position.x);
		float rot = angle * (180 / PI);

		if (TimeManager::GetDeltaTime() < 0.1f)
		{
			transform->SetRotation(rot);
			if (GridManager::grid[x][y] == Grid::WATER)
			{
				transform->position.x += cosf(angle) * (moveSpeed / 2) * TimeManager::GetDeltaTime();
				transform->position.y += sinf(angle) * (moveSpeed / 2) * TimeManager::GetDeltaTime();
			}
			else
			{
				transform->position.x += cosf(angle) * moveSpeed * TimeManager::GetDeltaTime();
				transform->position.y += sinf(angle) * moveSpeed * TimeManager::GetDeltaTime();
			}
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
	else
	{
		if (GridManager::grid[x][y] == Grid::EMPTY)
			GridManager::grid[x][y] = Grid::OBSTACLE;
		transform->SetPosition(GameManager::GetInstance()->GetGridPos(x, y));
	}

	if (attackMotion == true)
		AttackMotion();
}

void SoldierAnt::SetDest()
{
	isStop = true;
	if (GridManager::grid[x][y] == Grid::OBSTACLE)
		GridManager::grid[x][y] = Grid::EMPTY;
	moveList.clear();
	moveList = gridManager->SetDest(x, y, destX, destY);
	if (!moveList.empty())
	{
		isStop = false;
	}
}

void SoldierAnt::ResetDest()
{
	int cnt = 0;
	bool reFindDest = false;
	while (!reFindDest)
	{
		for (int i = -cnt; i <= cnt; i++)
		{
			for (int j = -cnt; j <= cnt; j++)
			{
				if (destX + i < 0 || destX + i >= X_SIZE || destY + j < 0 || destY + j >= Y_SIZE)
					continue;
				if ((GridManager::grid[destX + i][destY + j] == Grid::EMPTY || GridManager::grid[destX + i][destY + j] == Grid::WATER || GridManager::grid[destX + i][destY + j] == Grid::BUSH) && rand() % 4 == 0)
				{
					reFindDest = true;
					destX += i;
					destY += j;
					std::cout << destX << " " << destY << std::endl;
					break;
				}
			}
			if (reFindDest)
				break;
		}
		cnt++;
	}
	SetDest();
}

void SoldierAnt::AttackAvail()
{
	timeCheck += TimeManager::GetDeltaTime();

	if (timeCheck >= timeCount)
	{
		attackAvail = true;
		timeCheck = 0;

	}
}

void SoldierAnt::AttackMotion()
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
