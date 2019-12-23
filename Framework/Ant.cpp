#include "stdafx.h"
#include "Ant.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Scene.h"
#include "GameManager.h"

#define PI 3.1415926535f

Ant::Ant(int x, int y) :
	GameObject(L"resources/sprites/ant_1.png", GameManager::GetInstance()->GetGridPos(x, y)), moveSpeed(200),
	x(x), y(y), destX(x), destY(y), isStop(true), isSelected(false), isCarrying(false)
{
	transform->SetScale(0.4f, 0.4f);
	col = new CircleCollider(*transform, 2.f);
	gridManager = new GridManager();
	moveList.clear();
	//GridManager::grid[x][y] = Grid::OBSTACLE;
	state = StatusUI::ANTHOUSE;

	attackAvail = false;
	timeCheck = 0.f;
	timeCount = 2.f;

	curCameraPos = GameManager::GetInstance()->cameraPos;
}

Ant::~Ant()
{
	SAFE_DELETE(col);
	SAFE_DELETE(gridManager);
}

void Ant::Update()
{
	//if (InputManager::GetKeyDown(VK_LBUTTON))
	//{
	//	int tempX = InputManager::GetMouseX();
	//	tempX -= 40;
	//	int tempY = InputManager::GetMouseY();
	//	tempY -= 44;
	//	if (tempX >= 0 && tempX <= 1464 && tempY >= 0 && tempY <= 816)
	//	{
	//		tempX /= GRID_SIZE;
	//		tempY /= GRID_SIZE;
	//		destX = tempX;
	//		destY = tempY;
	//		SetDest();
	//	}
	//}

	if (!isStop)
	{
		Move();
		if (isCarrying)
		{
			switch (state)
			{
			case UI_BUILD_1:
				ChangeSprite(ANT_BUILD_1);
				break;
			case UI_BUILD_2:
				ChangeSprite(ANT_BUILD_2);
				break;
			case UI_BUILD_3:
				ChangeSprite(ANT_BUILD_3);
				break;
			case UI_FOOD_1:
				ChangeSprite(ANT_FOOD_1);
				break;
			case UI_FOOD_2:
				ChangeSprite(ANT_FOOD_2);
				break;
			case UI_FOOD_3:
				ChangeSprite(ANT_FOOD_3);
				break;
			case UI_FOOD_4:
				ChangeSprite(ANT_FOOD_4);
				break;
			case UI_FOOD_5:
				ChangeSprite(ANT_FOOD_5);
				break;
			case UI_FOOD_6:
				ChangeSprite(ANT_FOOD_6);
				break;
			case UI_FOOD_7:
				ChangeSprite(ANT_FOOD_7);
				break;
			case UI_FOOD_8:
				ChangeSprite(ANT_FOOD_8);
				break;
			case UI_FOOD_9:
				ChangeSprite(ANT_FOOD_9);
				break;
			case UI_FOOD_10:
				ChangeSprite(ANT_FOOD_10);
				break;
			case UI_TRASH_1:
				ChangeSprite(ANT_TRASH_1);
				break;
			case UI_TRASH_2:
				ChangeSprite(ANT_TRASH_2);
				break;
			case UI_TRASH_3:
				ChangeSprite(ANT_TRASH_3);
				break;
			case UI_TRASH_4:
				ChangeSprite(ANT_TRASH_4);
				break;
			case UI_TRASH_5:
				ChangeSprite(ANT_TRASH_5);
				break;
			}
		}
		else if (isSelected)
			ChangeSprite(ANT_SELECTED);
		else
			ChangeSprite(ANT_IDLE);
	}
	else
	{
		//if (GridManager::grid[x][y] == Grid::EMPTY)
		//	GridManager::grid[x][y] = Grid::OBSTACLE;
		if (isSelected)
			ChangeSprite(ANT_SELECTED);
		else
			ChangeSprite(ANT_IDLE);
		transform->SetPosition(GameManager::GetInstance()->GetGridPos(x, y));
	}
}

void Ant::ChangeSprite(AntSprite a)
{
	switch (a)
	{
	case ANT_IDLE:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/ant_1.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_SELECTED:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/ant_1_selected.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_BUILD_1:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_leaf.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_BUILD_2:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_wood.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_BUILD_3:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_bigwood.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_FOOD_1:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_bread.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_FOOD_2:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_ice.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_FOOD_3:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_snack.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_FOOD_4:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_pizza.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_FOOD_5:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_chicken.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_FOOD_6:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_carrot.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_FOOD_7:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_popcorn.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_FOOD_8:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_fish.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_FOOD_9:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_cotton.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_FOOD_10:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_grasshopper.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_TRASH_1:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_tissue.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_TRASH_2:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_bottle.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_TRASH_3:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_can.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_TRASH_4:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_mask.png", 0, 0));
		renderer->SetLayer(1);
		break;
	case ANT_TRASH_5:
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/objectAnt/ant_1_lunch.png", 0, 0));
		renderer->SetLayer(1);
		break;
	}
}

void Ant::Move()
{
	Vector2 tempDest = GameManager::GetInstance()->GetGridPos(moveList.front().x, moveList.front().y);

	float angle = atan2f(tempDest.y - transform->position.y, tempDest.x - transform->position.x);
	float rot = angle * (180 / PI);
	float rotRate = (rot - transform->rotatingAngle) / 2.f;

	//std::cout << rot << " " << rotRate << std::endl;
	//if ((rot - 180) * (transform->rotatingAngle - 180) < 0)
	//	rotRate = (transform->rotatingAngle - rot) / 3.f;
	//else
	//	rotRate = (rot - transform->rotatingAngle) / 3.f;
	//if (abs(rot - transform->rotatingAngle) < 10)
	//{
	//	transform->position.x += cosf(angle) * moveSpeed * TimeManager::GetDeltaTime();
	//	transform->position.y += sinf(angle) * moveSpeed * TimeManager::GetDeltaTime();
	//}
	if (TimeManager::GetDeltaTime() < 0.1f)
	{
		//transform->SetRotation(transform->rotatingAngle + rotRate);
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
			if (isCarrying)
			{
				isCarrying = false;
			}
			destX = x;
			destY = y;
			//if (GridManager::grid[x][y] == Grid::EMPTY)
			//	GridManager::grid[x][y] = Grid::OBSTACLE;
			transform->SetPosition(GameManager::GetInstance()->GetGridPos(x, y));
			if (isSelected)
				ChangeSprite(ANT_SELECTED);
			else
				ChangeSprite(ANT_IDLE);
			isStop = true;
		}
	}
}

void Ant::SetDest()
{
	isStop = true;
	//if (GridManager::grid[x][y] == Grid::OBSTACLE)
	//	GridManager::grid[x][y] = Grid::EMPTY;
	moveList.clear();
	moveList = gridManager->SetDest(x, y, destX, destY);
	if (!moveList.empty())
	{
		if (isSelected)
			ChangeSprite(ANT_SELECTED);
		else
			ChangeSprite(ANT_IDLE);
		isStop = false;
	}
}

void Ant::ResetDest()
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
					std::cout << "a : " << destX << " " << destY << std::endl;
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

void Ant::SetCarry(StatusUI state)
{
	isCarrying = true;
	isSelected = false;
	this->state = state;
	destX = 120;
	destY = 67;
	ResetDest();
}

void Ant::AttackAvail()
{

	timeCheck += TimeManager::GetDeltaTime();

	if (timeCheck >= timeCount)
	{
		attackAvail = true;
		timeCheck = 0;

	}
}

//�� ��� ������	: 1600 x 900
//���� �� ������	: 1584 x 864 (�׵θ����� ���� 8px, ���� 18px �� ��)
//�׸��� 1			: 48px (��ü 33 x 18)
//�׸��� 2			: 24px (��ü 66 x 36)
//���� ����

//�� ������			: 1464 x 824 (ȭ�� �׵θ����� 40px �� ��)
//���� �� ������	: 1464 x 816 (��� �׵θ����� ���� 4px �� ��)
//�׸���			: 24px (��ü 61 x 34)
//���� 40px, ���� 44px �� ��

//(ä��)
//�� ������			: 5760 x 3240
//�׸���			: 24px (��ü 240 x 135)