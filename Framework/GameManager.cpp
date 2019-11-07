#include "stdafx.h"
#include "GameManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "GameOverScene.h"

GameManager::GameManager()
{
	antManager = (AntManager*)Scene::GetCurrentScene().PushBackGameObject(new AntManager());
	antHouse = (AntHouse*)Scene::GetCurrentScene().PushBackGameObject(new AntHouse(13, 18, antManager));

	GameObject* selectedStatus_basic = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/UI/status/basic_status.png", Vector2(365.f, 972.f)));
	selectedStatus_basic->renderer->SetLayer(3);

	objectManager = (ObjectManager*)Scene::GetCurrentScene().PushBackGameObject(new ObjectManager());
	dayManager = (DayManager*)Scene::GetCurrentScene().PushBackGameObject(new DayManager());
	charStatus = (CharacterStatusUI*)Scene::GetCurrentScene().PushBackGameObject(new CharacterStatusUI());
	selectedStatus = (SelectedStatusUI*)Scene::GetCurrentScene().PushBackGameObject(new SelectedStatusUI());
	selectedButton = (SelectedButton*)Scene::GetCurrentScene().PushBackGameObject(new SelectedButton(1350, 972));

	houseupButton = (PlusButton*)Scene::GetCurrentScene().PushBackGameObject(new PlusButton(815, 972, 0));
	sheildaddButton = (PlusButton*)Scene::GetCurrentScene().PushBackGameObject(new PlusButton(1015, 972, 1));

	selectedStatus->SetActive(false);
	selectedButton->SetActive(false);

	oldX = curX = InputManager::GetMouseX();
	oldY = curY = InputManager::GetMouseY();

	ping = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/UI/ping.png"));
	ping->renderer->SetLayer(3);
	ping->renderer->SetAlpha(0.f);
	ping->transform->SetScale(0.8f, 0.8f);
	ping->transform->positioningCenter = Vector2(0.f, 34.f);
	ping->SetActive(false);

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

	SetWaterObstacle();
}

GameManager::~GameManager()
{

}

void GameManager::Update()
{
	CheckMouseAction();

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

void GameManager::SetWaterObstacle()
{
	for (int i = 0; i < 45; i++)
	{
		int cnt;
		if (i <= 19)
			cnt = 3;
		else if (i <= 30)
			cnt = 4;
		else if (i <= 34)
			cnt = 3;
		else if (i <= 39)
			cnt = 2;
		else
			cnt = 1;

		for (int j = 0; j < cnt; j++)
		{
			GridManager::grid[i][j] = Grid::OBSTACLE;
		}
	}
}

void GameManager::CheckMouseAction()
{

	if (tempBush == nullptr)
	{

		if (InputManager::GetKeyDown(VK_LBUTTON))
		{
			for (auto& i : currentAntGroup)
			{
				i->isSelected = false;
			}
			currentAntGroup.clear();
			int tempX = InputManager::GetMouseX();
			int tempY = InputManager::GetMouseY();
			tempX -= 40;
			tempY -= 44;
			if (tempX >= 0 && tempX <= 1464 && tempY >= 0 && tempY <= 816)
			{
				drag->SetActive(true);
				dragX = tempX + 40.f;
				dragY = tempY + 44.f;
				drag->transform->SetPosition(dragX, dragY);

				tempX /= GRID_SIZE;
				tempY /= GRID_SIZE;

				oldX = tempX;
				oldY = tempY;
			}
		}
		else if (InputManager::GetKeyPressed(VK_LBUTTON))
		{
			int tempX = InputManager::GetMouseX();
			int tempY = InputManager::GetMouseY();
			tempX -= 40;
			tempY -= 44;
			if (tempX >= 0 && tempX <= 1464 && tempY >= 0 && tempY <= 816)
			{
				drag->transform->SetPosition((tempX + 40.f + dragX) / 2.f, (tempY + 44.f + dragY) / 2.f);
				drag->transform->SetScale(((tempX + 40.f) - dragX) / 1464.f, ((tempY + 44.f) - dragY) / 816.f);

				tempX /= GRID_SIZE;
				tempY /= GRID_SIZE;
			}
		}
		else if (InputManager::GetKeyUp(VK_LBUTTON))
		{
			int tempX = InputManager::GetMouseX();
			int tempY = InputManager::GetMouseY();
			tempX -= 40;
			tempY -= 44;
			if (tempX >= 0 && tempX <= 1464 && tempY >= 0 && tempY <= 816)
			{
				tempX /= GRID_SIZE;
				tempY /= GRID_SIZE;

				curX = tempX;
				curY = tempY;

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
								currentAntGroup.push_back(i);
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
									currentAntGroup.push_back(a);
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
				tempX /= GRID_SIZE;
				tempY /= GRID_SIZE;

				curX = tempX;
				curY = tempY;

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
								currentAntGroup.push_back(a);
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
			tempY -= 44;
			if (tempX >= 0 && tempX <= 1464 && tempY >= 0 && tempY <= 816)
			{
				tempX /= GRID_SIZE;
				tempY /= GRID_SIZE;

				if (GridManager::grid[tempX][tempY] != Grid::OBSTACLE && !currentAntGroup.empty())
				{
					SetPing(tempX, tempY);
					for (auto& i : currentAntGroup)
					{
						i->destX = tempX;
						i->destY = tempY;
						i->ResetDest();
					}
				}
			}
		}

		if (ping->GetActive())
		{
			ping->renderer->SetAlpha(ping->renderer->GetAlpha() - 0.01f);
			if (ping->renderer->GetAlpha() <= 0.f)
			{
				ping->renderer->SetAlpha(0.f);
				ping->SetActive(false);
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
			else if (sheildaddButton->col->Intersected(InputManager::GetMouseVector2()))
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

void GameManager::SetPing(int x, int y)
{
	ping->SetActive(true);
	ping->transform->SetPosition(52 + x * GRID_SIZE, 56 + y * GRID_SIZE);
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
		tempBush = (Bush*)Scene::GetCurrentScene().PushBackGameObject(new Bush());
		charStatus->woodValue -= 6;
		charStatus->Notify();
	}
}
