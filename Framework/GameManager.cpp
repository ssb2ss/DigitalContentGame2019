#include "stdafx.h"
#include "GameManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "GameOverScene.h"

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::GetInstance()
{
	return instance;
}

GameManager::GameManager()
{
	if (instance == nullptr)
	{
		instance = this;
	}
	else
	{
		Scene::GetCurrentScene().Destroy(this);
	}

	mapBackground = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/background/bigmap_1.png", Vector2(772.f, 452.f)));
	mapBackground->renderer->SetLayer(0);
	gridBG = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/biggrid.png", Vector2(772.f, 452.f)));
	gridBG->renderer->SetLayer(0);
	gridBG->renderer->SetAlpha(0.5f);

	SetObstacle(1);

	antManager = (AntManager*)Scene::GetCurrentScene().PushBackGameObject(new AntManager());
	enemyManager = (EnemyManager*)Scene::GetCurrentScene().PushBackGameObject(new EnemyManager());

	fightManager = (FightManager*)Scene::GetCurrentScene().PushBackGameObject(new FightManager());
	antHouse = (AntHouse*)Scene::GetCurrentScene().PushBackGameObject(new AntHouse(13, 18));

	GameObject* selectedStatus_basic = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/UI/status/basic_status.png", Vector2(365.f, 972.f)));
	selectedStatus_basic->renderer->SetLayer(3);

	objectManager = (ObjectManager*)Scene::GetCurrentScene().PushBackGameObject(new ObjectManager());
	dayManager = (DayManager*)Scene::GetCurrentScene().PushBackGameObject(new DayManager());
	charStatus = (CharacterStatusUI*)Scene::GetCurrentScene().PushBackGameObject(new CharacterStatusUI());
	selectedStatus = (SelectedStatusUI*)Scene::GetCurrentScene().PushBackGameObject(new SelectedStatusUI());
	selectedButton = (SelectedButton*)Scene::GetCurrentScene().PushBackGameObject(new SelectedButton(1350, 972));

	FontObject* str = (FontObject*)Scene::GetCurrentScene().PushBackGameObject(new FontObject(L"남은 개미 : ", Vector2(1620, 20), 0, Vector2(1, 1), L"Arial", 30, 1, 1, 1, 1, true));
	str->renderer->SetLayer(3);
	_itow_s<4>(antManager->antList.size(), antNumber, 10);
	antNumberText = (FontObject*)Scene::GetCurrentScene().PushBackGameObject(new FontObject(antNumber, Vector2(1780, 25), 0, Vector2(1, 1), L"Arial", 30, 1, 1, 1, 1, true));
	antNumberText->renderer->SetLayer(3);

	FontObject* str2 = (FontObject*)Scene::GetCurrentScene().PushBackGameObject(new FontObject(L"DAY ", Vector2(1340, 870), 0, Vector2(1, 1), L"Arial", 50, 1, 1, 1, 1, true));
	str2->renderer->SetLayer(3);
	_itow_s<4>(DayManager::dayCount, dayNumber, 10);
	dayNumberText = (FontObject*)Scene::GetCurrentScene().PushBackGameObject(new FontObject(dayNumber, Vector2(1455, 870), 0, Vector2(1, 1), L"Arial", 50, 1, 1, 1, 1, true));
	dayNumberText->renderer->SetLayer(3);

	houseupButton = (PlusButton*)Scene::GetCurrentScene().PushBackGameObject(new PlusButton(815, 972, 0));
	shieldaddButton = (PlusButton*)Scene::GetCurrentScene().PushBackGameObject(new PlusButton(1015, 972, 1));

	selectedStatus->SetActive(false);
	selectedButton->SetActive(false);

	oldX = curX = InputManager::GetMouseX();
	oldY = curY = InputManager::GetMouseY();

	ping = (Ping*)Scene::GetCurrentScene().PushBackGameObject(new Ping());

	drag = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/UI/drag.png"));
	drag->renderer->SetLayer(3);
	drag->renderer->SetAlpha(0.5f);
	drag->transform->SetPosition(0.f, 0.f);
	drag->transform->SetScale(0.f, 0.f);
	drag->SetActive(false);
	dragX = dragY = 0;

	noAnt = (NoAntUI*)Scene::GetCurrentScene().PushBackGameObject(new NoAntUI());
	noAnt->SetActive(false);

	tempBush = nullptr;

	currentDay = 1;

	cameraPos = Vector2(0, 0);
	cameraSpeed = 20.f;


}

GameManager::~GameManager()
{

}

void GameManager::Update()
{

	CheckMouseAction();
	ManageAnt();
	ManageDay();
	ManageCamera();
	ChangeDay();

	if (InputManager::GetKeyDown(VK_LBUTTON))
	{
		Vector2 m = InputManager::GetMouseVector2();
		if (m.x - 40 >= 0 && m.x - 40 <= 1464 && m.y - 40 >= 0 && m.y - 40 <= 824)
			std::cout << "x : " << GetPosGridX(m) << " , y : " << GetPosGridY(m) << std::endl;
	}

}

Vector2 GameManager::GetGridPos(int x, int y)
{
	Vector2 res;

	res.x = x * GRID_SIZE;
	res.x -= 2096 + cameraPos.x;
	res.y = y * GRID_SIZE;
	res.y -= 1156 + cameraPos.y;

	return res;
}

int GameManager::GetPosGridX(Vector2 pos)
{
	float x = pos.x;
	x += 2108 + cameraPos.x;
	int res = x / GRID_SIZE;
	return res;
}

int GameManager::GetPosGridX(float _x)
{
	float x = _x;
	x += 2108 + cameraPos.x;
	int res = x / GRID_SIZE;
	return res;
}

int GameManager::GetPosGridY(Vector2 pos)
{
	float y = pos.y;
	y += 1168 + cameraPos.y;
	int res = y / GRID_SIZE;
	return res;
}

int GameManager::GetPosGridY(float _y)
{
	float y = _y;
	y += 1168 + cameraPos.y;
	int res = y / GRID_SIZE;
	return res;
}

void GameManager::SetObstacle(int map)
{

	//맵에 따른 그리드 설정
	if (map == 1)
	{

	}
	else if (map == 2)
	{

	}
	else if (map == 3)
	{

	}
	else if (map == 4)
	{

	}
}

void GameManager::CheckMouseAction()
{

	if (tempBush == nullptr)
	{

		if (InputManager::GetKeyDown(VK_LBUTTON))
		{
			for (auto& i : antManager->currentAntGroup)
			{
				i->isSelected = false;
			}
			antManager->currentAntGroup.clear();
			int tempX = InputManager::GetMouseX();
			int tempY = InputManager::GetMouseY();
			tempX -= 40;
			tempY -= 40;
			if (tempX >= 0 && tempX <= 1464 && tempY >= 0 && tempY <= 824)
			{
				tempX += 40;
				tempY += 40;

				drag->SetActive(true);
				dragX = tempX;
				dragY = tempY;
				drag->transform->SetPosition(dragX, dragY);

				oldX = GetPosGridX(tempX);
				oldY = GetPosGridY(tempY);
			}
		}
		else if (InputManager::GetKeyPressed(VK_LBUTTON))
		{
			int tempX = InputManager::GetMouseX();
			int tempY = InputManager::GetMouseY();
			tempX -= 40;
			tempY -= 40;
			if (tempX >= 0 && tempX <= 1464 && tempY >= 0 && tempY <= 824)
			{
				tempX += 40;
				tempY += 40;

				drag->transform->SetPosition((tempX + dragX) / 2.f, (tempY + dragY) / 2.f);
				drag->transform->SetScale((tempX - dragX) / 1464.f, (tempY - dragY) / 816.f);
			}
		}
		else if (InputManager::GetKeyUp(VK_LBUTTON))
		{
			int tempX = InputManager::GetMouseX();
			int tempY = InputManager::GetMouseY();
			tempX -= 40;
			tempY -= 40;
			if (tempX >= 0 && tempX <= 1464 && tempY >= 0 && tempY <= 824)
			{
				tempX += 40;
				tempY += 40;

				curX = GetPosGridX(tempX);
				curY = GetPosGridY(tempY);

				if (curX == oldX && curY == oldY)
				{
					if (GridManager::grid[curX][curY] == Grid::EMPTY || GridManager::grid[curX][curY] == Grid::OBSTACLE)
					{
						selectedStatus->SetState(StatusUI::ANTHOUSE);
						selectedStatus->SetActive(false);
						selectedButton->SetActive(false);
						for (auto& i : antManager->antList)
						{
							if (i->x == curX && i->y == curY)
							{
								antManager->currentAntGroup.push_back(i);
								i->isSelected = true;
								break;
							}
						}
					}
					else if (GridManager::grid[curX][curY] == Grid::HOUSE)
						SetSelectedUI(StatusUI::ANTHOUSE, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::BUILD_1)
						SetSelectedUI(StatusUI::UI_BUILD_1, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::BUILD_2)
						SetSelectedUI(StatusUI::UI_BUILD_2, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::BUSH)
						SetSelectedUI(StatusUI::UI_BUSH, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::FOOD_1)
						SetSelectedUI(StatusUI::UI_FOOD_1, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::FOOD_2)
						SetSelectedUI(StatusUI::UI_FOOD_2, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::FOOD_3)
						SetSelectedUI(StatusUI::UI_FOOD_3, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::FOOD_4)
						SetSelectedUI(StatusUI::UI_FOOD_4, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::FOOD_5)
						SetSelectedUI(StatusUI::UI_FOOD_5, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::TRASH_1)
						SetSelectedUI(StatusUI::UI_TRASH_1, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::TRASH_2)
						SetSelectedUI(StatusUI::UI_TRASH_2, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::TRASH_3)
						SetSelectedUI(StatusUI::UI_TRASH_3, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::WATER)
						SetSelectedUI(StatusUI::UI_WATER, curX, curY);
				}
				else
				{
					if (curX < oldX)
					{
						int tem = curX;
						curX = oldX;
						oldX = tem;
					}
					if (curY < oldY)
					{
						int tem = curY;
						curY = oldY;
						oldY = tem;
					}

					for (int i = oldX; i <= curX; i++)
					{
						for (int j = oldY; j <= curY; j++)
						{
							for (auto& a : antManager->antList)
							{
								if (a->x == i && a->y == j && !a->isCarrying)
								{
									antManager->currentAntGroup.push_back(a);
									a->isSelected = true;
								}
							}
						}
					}
				}

				curX = curY = oldX = oldY = 0;
			}
			else if (drag->GetActive())
			{
				tempX += 40;
				tempY += 40;

				curX = GetPosGridX(tempX);
				curY = GetPosGridY(tempY);

				if (curX < oldX)
				{
					int tem = curX;
					curX = oldX;
					oldX = tem;
				}
				if (curY < oldY)
				{
					int tem = curY;
					curY = oldY;
					oldY = tem;
				}

				for (int i = oldX; i <= curX; i++)
				{
					for (int j = oldY; j <= curY; j++)
					{
						for (auto& a : antManager->antList)
						{
							if (a->x == i && a->y == j && !a->isCarrying)
							{
								antManager->currentAntGroup.push_back(a);
								a->isSelected = true;
							}
						}
					}
				}
			}


			drag->transform->SetPosition(0.f, 0.f);
			drag->transform->SetScale(0.f, 0.f);
			drag->SetActive(false);
			dragX = dragY = 0;
		}

		if (InputManager::GetKeyDown(VK_RBUTTON))
		{
			int tempX = InputManager::GetMouseX();
			int tempY = InputManager::GetMouseY();
			tempX -= 40;
			tempY -= 40;
			if (tempX >= 0 && tempX <= 1464 && tempY >= 0 && tempY <= 824)
			{
				tempX += 40;
				tempY += 40;

				tempX = GetPosGridX(tempX);
				tempY = GetPosGridY(tempY);

				if (GridManager::grid[tempX][tempY] != Grid::OBSTACLE && !antManager->currentAntGroup.empty())
				{
					SetPing(tempX, tempY);
					for (auto& i : antManager->currentAntGroup)
					{
						i->destX = tempX;
						i->destY = tempY;
						i->ResetDest();
					}
				}
			}
		}

		if (InputManager::GetKeyDown(VK_LBUTTON))
		{
			if (selectedButton->col->Intersected(InputManager::GetMouseVector2()) && selectedButton->GetActive())
			{
				OnClickSelectedButton();
			}
			else if (houseupButton->col->Intersected(InputManager::GetMouseVector2()))
			{
				OnHouseUp();
			}
			else if (shieldaddButton->col->Intersected(InputManager::GetMouseVector2()))
			{
				OnShieldAdd();
			}
		}

	}
	else
	{
		if (tempBush->isSet)
			tempBush = nullptr;
	}

}

void GameManager::ManageAnt()
{
	std::list<Ant*> tempList;
	int cnt[12] = { 0, };
	for (auto& i : antManager->antList)
	{
		if (i->state != ANTHOUSE && !i->isCarrying)
		{
			cnt[i->state]++;
			tempList.push_back(i);
		}
	}
	for (int i = 0; i < 12; i++)
	{
		if (i != ANTHOUSE && i != UI_BUSH && i != UI_WATER)
		{
			if (cnt[i] == selectedStatus->value[i].ant)
			{
				for (auto& a : tempList)
				{
					a->state = ANTHOUSE;
				}
				charStatus->waterValue += selectedStatus->value[i].water;
				charStatus->foodValue += selectedStatus->value[i].food;
				charStatus->woodValue += selectedStatus->value[i].wood;
				charStatus->Notify();
				selectedStatus->SetState(ANTHOUSE);
				selectedStatus->SetActive(false);
			}
		}
	}

	_itow_s<4>(antManager->antList.size(), antNumber, 10);
	antNumberText->SetText(antNumber);

}

void GameManager::ChangeDay()
{
	_itow_s<4>(DayManager::dayCount, dayNumber, 10);
}

void GameManager::ManageDay()
{
	if (dayManager->dayCount - currentDay == 1 && dayManager->dayCount == 2)
	{
		selectedStatus->SetState(ANTHOUSE);
		selectedStatus->SetActive(false);
		selectedButton->SetActive(false);

		antDieCheck = 0;
		for (auto& i : antManager->antList)
		{
			if (GridManager::grid[i->x][i->y] == Grid::BUSH)
			{
				continue;
			}
			antManager->Destroy(i);
			++antDieCheck;
			if (antHouse->GetLevel() == 1)
			{
				if (antDieCheck >= 4)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 2)
			{
				if (antDieCheck >= 3)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 3)
			{
				if (antDieCheck >= 2)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 4)
			{
				if (antDieCheck >= 1)
				{
					break;
				}
			}
		}

		currentDay = dayManager->dayCount;

		charStatus->waterValue -= 4;
		charStatus->foodValue -= 4;
		charStatus->Notify();

	}
	else if (dayManager->dayCount - currentDay == 1 && dayManager->dayCount == 3)
	{
		selectedStatus->SetState(ANTHOUSE);
		selectedStatus->SetActive(false);
		selectedButton->SetActive(false);

		antDieCheck = 0;
		for (auto& i : antManager->antList)
		{
			if (GridManager::grid[i->x][i->y] == Grid::BUSH)
			{
				continue;
			}
			antManager->Destroy(i);
			++antDieCheck;
			if (antHouse->GetLevel() == 1)
			{
				if (antDieCheck >= 14)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 2)
			{
				if (antDieCheck >= 10)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 3)
			{
				if (antDieCheck >= 7)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 4)
			{
				if (antDieCheck >= 4)
				{
					break;
				}
			}
		}

		currentDay = dayManager->dayCount;

		charStatus->waterValue -= 4;
		charStatus->foodValue -= 4;
		charStatus->Notify();

	}
	else if (dayManager->dayCount - currentDay == 1 && dayManager->dayCount == 4)
	{
		selectedStatus->SetState(ANTHOUSE);
		selectedStatus->SetActive(false);
		selectedButton->SetActive(false);

		antDieCheck = 0;
		for (auto& i : antManager->antList)
		{
			if (GridManager::grid[i->x][i->y] == Grid::BUSH)
			{
				continue;
			}
			antManager->Destroy(i);
			++antDieCheck;
			if (antHouse->GetLevel() == 1)
			{
				if (antDieCheck >= 24)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 2)
			{
				if (antDieCheck >= 17)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 3)
			{
				if (antDieCheck >= 10)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 4)
			{
				if (antDieCheck >= 6)
				{
					break;
				}
			}
		}

		currentDay = dayManager->dayCount;

		charStatus->waterValue -= 4;
		charStatus->foodValue -= 4;
		charStatus->Notify();

	}
}

void GameManager::ManageCamera()
{

	if (InputManager::GetKeyPressed('W'))
	{
		cameraPos.y -= cameraSpeed;
	}
	else if (InputManager::GetKeyPressed('S'))
	{
		cameraPos.y += cameraSpeed;
	}
	if (InputManager::GetKeyPressed('A'))
	{
		cameraPos.x -= cameraSpeed;
	}
	else if (InputManager::GetKeyPressed('D'))
	{
		cameraPos.x += cameraSpeed;
	}

	if (cameraPos.x > 2148)
	{
		cameraPos.x = 2148;
	}
	else if (cameraPos.x < -2148)
	{
		cameraPos.x = -2148;
	}

	if (cameraPos.y > 1208)
	{
		cameraPos.y = 1208;
	}
	else if (cameraPos.y < -1208)
	{
		cameraPos.y = -1208;
	}

	mapBackground->transform->SetPosition(Vector2(772.f - cameraPos.x, 452.f - cameraPos.y));
	gridBG->transform->SetPosition(Vector2(772.f - cameraPos.x, 452.f - cameraPos.y));

	antHouse->transform->SetPosition(GetGridPos(antHouse->x, antHouse->y));
	ping->transform->SetPosition(GetGridPos(ping->x, ping->y));
	for (auto& i : antManager->antList)
	{
		i->transform->position += i->curCameraPos - cameraPos;
		i->curCameraPos = cameraPos;
	}
	for (auto& i : enemyManager->enemyList)
		i->transform->SetPosition(GetGridPos(i->x, i->y));
	for (auto& i : objectManager->buildList)
		i->transform->SetPosition(GetGridPos(i->x, i->y));
	for (auto& i : objectManager->bushList)
		i->transform->SetPosition(GetGridPos(i->x, i->y));
	for (auto& i : objectManager->foodList)
		i->transform->SetPosition(GetGridPos(i->x, i->y));
	for (auto& i : objectManager->footPrintList)
		i->transform->SetPosition(GetGridPos(i->x, i->y));
	for (auto& i : objectManager->stoneList)
		i->transform->SetPosition(GetGridPos(i->x, i->y));
	for (auto& i : objectManager->trashList)
		i->transform->SetPosition(GetGridPos(i->x, i->y));
	for (auto& i : objectManager->waterList)
		i->transform->SetPosition(GetGridPos(i->x, i->y));
	

}

void GameManager::SetPing(int x, int y)
{
	ping->SetActive(true);
	ping->x = x;
	ping->y = y;
	ping->transform->SetPosition(GetGridPos(x, y));
	ping->renderer->SetAlpha(1.f);
}

void GameManager::SetSelectedUI(StatusUI state, int x, int y)
{
	selectedStatus->SetActive(true);
	selectedStatus->SetState(state);
	selectedButton->SetActive(true);
	selectedButton->SetState(state, x, y);
}

void GameManager::OnClickSelectedButton()
{
	int x = selectedButton->x;
	int y = selectedButton->y;
	StatusUI state = selectedButton->state;

	int max = INT_MAX;
	std::list<Ant*> moveAntList;

	switch (state)
	{
		case ANTHOUSE:
			break;
		case UI_BUILD_1:
		{
			Build* temp = nullptr;
			for (auto& i : objectManager->buildList)
			{
				if (i->state == 1)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_BUILD_2:
		{
			Build* temp = nullptr;
			for (auto& i : objectManager->buildList)
			{
				if (i->state == 2)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_BUSH:
			break;
		case UI_FOOD_1:
		{
			Food* temp = nullptr;
			for (auto& i : objectManager->foodList)
			{
				if (i->state == 1)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_FOOD_2:
		{
			Food* temp = nullptr;
			for (auto& i : objectManager->foodList)
			{
				if (i->state == 2)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_FOOD_3:
		{
			Food* temp = nullptr;
			for (auto& i : objectManager->foodList)
			{
				if (i->state == 3)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_FOOD_4:
		{
			Food* temp = nullptr;
			for (auto& i : objectManager->foodList)
			{
				if (i->state == 4)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_FOOD_5:
		{
			Food* temp = nullptr;
			for (auto& i : objectManager->foodList)
			{
				if (i->state == 5)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_TRASH_1:
		{
			Trash* temp = nullptr;
			for (auto& i : objectManager->trashList)
			{
				if (i->state == 1)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_TRASH_2:
		{
			Trash* temp = nullptr;
			for (auto& i : objectManager->trashList)
			{
				if (i->state == 2)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_TRASH_3:
		{
			Trash* temp = nullptr;
			for (auto& i : objectManager->trashList)
			{
				if (i->state == 3)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_WATER:
		{
			Water* temp = nullptr;
			for (auto& i : objectManager->waterList)
			{
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < max)
				{
					max = gab;
					temp = i;
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			temp->isDestroy = true;
			charStatus->waterValue += selectedStatus->value[UI_WATER].water;
			charStatus->Notify();
			selectedStatus->SetState(ANTHOUSE);
			selectedStatus->SetActive(false);
			break;
		}
	}

	selectedButton->SetActive(false);
}

void GameManager::OnHouseUp()
{
	if (charStatus->woodValue >= antHouse->GetLevel() + 2)
	{
		if (antHouse->GetLevel() < 4)
		{
			antHouse->SetLevel(antHouse->GetLevel() + 1);
			charStatus->woodValue -= antHouse->GetLevel() + 2;
			charStatus->Notify();
		}
	}
}

void GameManager::OnShieldAdd()
{
	if (charStatus->woodValue >= 6)
	{
		tempBush = objectManager->PushBackObject(new Bush());
		charStatus->woodValue -= 6;
		charStatus->Notify();
	}
}
