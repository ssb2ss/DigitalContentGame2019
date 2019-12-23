#include "stdafx.h"
#include "Enemy.h"
#include "GridManager.h"
#include "TimeManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "Scene.h"

Enemy::Enemy(int x, int y, int state) :
	GameObject(L"resources/sprites/ant_ghost.png", GameManager::GetInstance()->GetGridPos(x, y)), x(x), y(y), destX(x), destY(y), state(state)
{
	transform->SetScale(0.5f, 0.5f);

	SetSprite(state);
	
	col = new CircleCollider(*transform, 120.f);
	moveCol = new CircleCollider(*transform, 2.f);
	attackAvail = false;
	timeCheck = 0.f;
	timeCount = 2.f;
	motionTimer = 0.f;
	attackMotion = false;
	isEnd = true;
	moveList.clear();
	moveCheck = true;
	saveTime = 0;
	moveSpeed = 100.f;
	hp = 5;

	curState = 1;
	
	grid = new GridManager();

	curCameraPos = GameManager::GetInstance()->cameraPos;
}


Enemy::~Enemy()
{
	SAFE_DELETE(col);
	SAFE_DELETE(moveCol);
	SAFE_DELETE(grid);
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
		//transform->SetPosition(GameManager::GetInstance()->GetGridPos(x, y));
	}

	if (InputManager::GetKeyDown(VK_LBUTTON) && col->Intersected(InputManager::GetMouseVector2()))
	{
		for (auto& i : GameManager::GetInstance()->antManager->soldierList)
		{
			i->target = &transform->position;
			i->destX = GameManager::GetInstance()->GetPosGridX(transform->position);
			i->destY = GameManager::GetInstance()->GetPosGridY(transform->position);
			i->SetDest();
		}
	}
	
}

void Enemy::Damage()
{
	--hp;
}
	

void Enemy::AttackAvail()
{
	moveSpeed = 0;

	timeCheck += TimeManager::GetDeltaTime();

	if (timeCheck >= timeCount)
	{
		attackAvail = true;
		timeCheck = 0;
	}
}

void Enemy::setDest()
{
	if (moveCheck)
	{
		isEnd = true;
		destX = rand() % 240;
		destY = rand() % 135;

		while (GridManager::grid[destX][destY] != Grid::EMPTY)
		{
			destX = rand() % 240;
			destY = rand() % 135;
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

	if (TimeManager::GetDeltaTime() < 0.1f)
	{
		transform->SetRotation(rot);
		transform->position.x += cosf(angle) * moveSpeed * TimeManager::GetDeltaTime();
		transform->position.y += sinf(angle) * moveSpeed * TimeManager::GetDeltaTime();
	}
	if (moveCol->Intersected(Vector2(tempDest.x, tempDest.y)))
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

	moveSpeed = 100.f;
}

void Enemy::SetSprite(int mode)
{
	if (mode == 1)
	{
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/cockroach.png", 0, 0));
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