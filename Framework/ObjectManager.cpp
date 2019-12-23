#include "stdafx.h"
#include "ObjectManager.h"
#include "Scene.h"
#include "GridManager.h"



ObjectManager::ObjectManager()
{
	dayCheck = DayManager::dayCount - 1;
	frameCount = 0;

	isGenerate = false;

	for (int i = 0; i < 3; i++)
		alert[i] = (wchar_t*)L"";

	FontObject* tempFont1 = (FontObject*)Scene::GetCurrentScene().PushBackGameObject(new FontObject(L"위치 : ", Vector2(1575.f, HEIGHT / 2 + 193 + 27), 0, Vector2(1, 1), L"Arial", 15, 0, 0, 0, 1, true));
	tempFont1->renderer->SetLayer(3);
	alertText[0] = (FontObject*)Scene::GetCurrentScene().PushBackGameObject(new FontObject(alert[0], Vector2(1620.f, HEIGHT / 2 + 193 + 27), 0, Vector2(1, 1), L"Arial", 15, 0, 0, 0, 1, true));
	alertText[0]->renderer->SetLayer(3);

	FontObject* tempFont2 = (FontObject*)Scene::GetCurrentScene().PushBackGameObject(new FontObject(L"위치 : ", Vector2(1575.f, HEIGHT / 2 + 297 + 27), 0, Vector2(1, 1), L"Arial", 15, 0, 0, 0, 1, true));
	tempFont2->renderer->SetLayer(3);
	alertText[1] = (FontObject*)Scene::GetCurrentScene().PushBackGameObject(new FontObject(alert[1], Vector2(1620.f, HEIGHT / 2 + 297 + 27), 0, Vector2(1, 1), L"Arial", 15, 0, 0, 0, 1, true));
	alertText[1]->renderer->SetLayer(3);

	FontObject* tempFont3 = (FontObject*)Scene::GetCurrentScene().PushBackGameObject(new FontObject(L"위치 : ", Vector2(1575.f, HEIGHT / 2 + 400 + 25), 0, Vector2(1, 1), L"Arial", 15, 0, 0, 0, 1, true));
	tempFont3->renderer->SetLayer(3);
	alertText[2] = (FontObject*)Scene::GetCurrentScene().PushBackGameObject(new FontObject(alert[2], Vector2(1620.f, HEIGHT / 2 + 400 + 25), 0, Vector2(1, 1), L"Arial", 15, 0, 0, 0, 1, true));
	alertText[2]->renderer->SetLayer(3);
}

ObjectManager::~ObjectManager()
{

}

Build* ObjectManager::PushBackObject(Build* b)
{
	Scene::GetCurrentScene().PushBackGameObject(b);
	buildList.push_back(b);
	return b;
}

Bush* ObjectManager::PushBackObject(Bush* b)
{
	Scene::GetCurrentScene().PushBackGameObject(b);
	bushList.push_back(b);
	return b;
}

Food* ObjectManager::PushBackObject(Food* f)
{
	Scene::GetCurrentScene().PushBackGameObject(f);
	foodList.push_back(f);
	return f;
}

FootPrint* ObjectManager::PushBackObject(FootPrint* f)
{
	Scene::GetCurrentScene().PushBackGameObject(f);
	footPrintList.push_back(f);
	return f;
}

Stone* ObjectManager::PushBackObject(Stone* s)
{
	Scene::GetCurrentScene().PushBackGameObject(s);
	stoneList.push_back(s);
	return s;
}

Trash* ObjectManager::PushBackObject(Trash* t)
{
	Scene::GetCurrentScene().PushBackGameObject(t);
	trashList.push_back(t);
	return t;
}

Water* ObjectManager::PushBackObject(Water* w)
{
	Scene::GetCurrentScene().PushBackGameObject(w);
	waterList.push_back(w);
	return w;
}


void ObjectManager::Destroy(Build* b)
{
	buildDestroyed.push_back(b);
}

void ObjectManager::Destroy(Bush* b)
{
	bushDestroyed.push_back(b);
}

void ObjectManager::Destroy(Food* f)
{
	foodDestroyed.push_back(f);
}

void ObjectManager::Destroy(FootPrint* f)
{
	footPrintDestroyed.push_back(f);
}

void ObjectManager::Destroy(Stone* s)
{
	stoneDestroyed.push_back(s);
}

void ObjectManager::Destroy(Trash* t)
{
	trashDestroyed.push_back(t);
}

void ObjectManager::Destroy(Water* w)
{
	waterDestroyed.push_back(w);
}


void ObjectManager::Update()
{
	/*
	if (DayManager::dayCount == dayCheck + 1)
	{
		++frameCount;
		if (frameCount >= 100 || dayCheck == 0)
		{
			for (auto& i : buildList)
				Destroy(i);
			for (auto& i : bushList)
				Destroy(i);
			for (auto& i : foodList)
				Destroy(i);
			for (auto& i : trashList)
				Destroy(i);
			for (auto& i : waterList)
				Destroy(i);
			dayCheck = DayManager::dayCount;


			if (DayManager::dayCount == 1)
			{
				for (int i = 0; i < 3;)
				{
					int tx = rand() % (X_SIZE - 4) + 2;
					int ty = rand() % (Y_SIZE - 2) + 1;
					int tstate = rand() % 4;

					while (GridManager::grid[tx][ty] != EMPTY ||
						GridManager::grid[tx + 1][ty] != EMPTY ||
						GridManager::grid[tx - 1][ty] != EMPTY ||
						GridManager::grid[tx][ty + 1] != EMPTY ||
						GridManager::grid[tx][ty - 1] != EMPTY ||
						GridManager::grid[tx + 1][ty + 1] != EMPTY ||
						GridManager::grid[tx + 1][ty - 1] != EMPTY ||
						GridManager::grid[tx - 1][ty + 1] != EMPTY ||
						GridManager::grid[tx - 1][ty - 1] != EMPTY)
					{
						tx = rand() % (X_SIZE - 4) + 2;
						ty = rand() % (Y_SIZE - 2) + 1;
					}
					PushBackObject(new Trash(tx, ty, tstate));
					i++;

				}

				for (int i = 0; i < 3;)
				{
					int tx = rand() % (X_SIZE - 4) + 2;
					int ty = rand() % (Y_SIZE - 2) + 1;
					int tstate = rand() % 10;

					while (GridManager::grid[tx][ty] != EMPTY ||
						GridManager::grid[tx + 1][ty] != EMPTY ||
						GridManager::grid[tx - 1][ty] != EMPTY ||
						GridManager::grid[tx][ty + 1] != EMPTY ||
						GridManager::grid[tx][ty - 1] != EMPTY ||
						GridManager::grid[tx + 1][ty + 1] != EMPTY ||
						GridManager::grid[tx + 1][ty - 1] != EMPTY ||
						GridManager::grid[tx - 1][ty + 1] != EMPTY ||
						GridManager::grid[tx - 1][ty - 1] != EMPTY)
					{
						tx = rand() % (X_SIZE - 4) + 2;
						ty = rand() % (Y_SIZE - 2) + 1;
					}
					PushBackObject(new Food(tx, ty, tstate));
					i++;

				}

				for (int i = 0; i < 1;)
				{
					int tx = rand() % (X_SIZE - 4) + 2;
					int ty = rand() % (Y_SIZE - 2) + 1;

					while (GridManager::grid[tx][ty] != EMPTY ||
						GridManager::grid[tx + 1][ty] != EMPTY ||
						GridManager::grid[tx - 1][ty] != EMPTY ||
						GridManager::grid[tx][ty + 1] != EMPTY ||
						GridManager::grid[tx][ty - 1] != EMPTY ||
						GridManager::grid[tx + 1][ty + 1] != EMPTY ||
						GridManager::grid[tx + 1][ty - 1] != EMPTY ||
						GridManager::grid[tx - 1][ty + 1] != EMPTY ||
						GridManager::grid[tx - 1][ty - 1] != EMPTY)
					{
						tx = rand() % (X_SIZE - 4) + 2;
						ty = rand() % (Y_SIZE - 2) + 1;
					}
					PushBackObject(new Water(tx, ty));
					i++;
				}


				for (int i = 0; i < 4;)
				{
					int tx = rand() % (X_SIZE - 4) + 2;
					int ty = rand() % (Y_SIZE - 2) + 1;
					int tstate = rand() % 3 + 1;

					while (GridManager::grid[tx][ty] != EMPTY ||
						GridManager::grid[tx + 1][ty] != EMPTY ||
						GridManager::grid[tx - 1][ty] != EMPTY ||
						GridManager::grid[tx][ty + 1] != EMPTY ||
						GridManager::grid[tx][ty - 1] != EMPTY ||
						GridManager::grid[tx + 1][ty + 1] != EMPTY ||
						GridManager::grid[tx + 1][ty - 1] != EMPTY ||
						GridManager::grid[tx - 1][ty + 1] != EMPTY ||
						GridManager::grid[tx - 1][ty - 1] != EMPTY)
					{
						tx = rand() % (X_SIZE - 4) + 2;
						ty = rand() % (Y_SIZE - 2) + 1;
					}
					PushBackObject(new Build(tx, ty, tstate));
					i++;

				}
			}
			else if (DayManager::dayCount == 2)
			{
				for (int i = 0; i < 2;)
				{
					int tx = rand() % (X_SIZE - 4) + 2;
					int ty = rand() % (Y_SIZE - 2) + 1;

					while (GridManager::grid[tx][ty] != EMPTY ||
						GridManager::grid[tx + 1][ty] != EMPTY ||
						GridManager::grid[tx - 1][ty] != EMPTY ||
						GridManager::grid[tx][ty + 1] != EMPTY ||
						GridManager::grid[tx][ty - 1] != EMPTY ||
						GridManager::grid[tx + 1][ty + 1] != EMPTY ||
						GridManager::grid[tx + 1][ty - 1] != EMPTY ||
						GridManager::grid[tx - 1][ty + 1] != EMPTY ||
						GridManager::grid[tx - 1][ty - 1] != EMPTY)
					{
						tx = rand() % (X_SIZE - 4) + 2;
						ty = rand() % (Y_SIZE - 2) + 1;
					}
					PushBackObject(new Water(tx, ty));
					i++;
				}


				for (int i = 0; i < 4;)
				{
					int tx = rand() % (X_SIZE - 4) + 2;
					int ty = rand() % (Y_SIZE - 2) + 1;
					int tstate = rand() % 3 + 1;

					while (GridManager::grid[tx][ty] != EMPTY ||
						GridManager::grid[tx + 1][ty] != EMPTY ||
						GridManager::grid[tx - 1][ty] != EMPTY ||
						GridManager::grid[tx][ty + 1] != EMPTY ||
						GridManager::grid[tx][ty - 1] != EMPTY ||
						GridManager::grid[tx + 1][ty + 1] != EMPTY ||
						GridManager::grid[tx + 1][ty - 1] != EMPTY ||
						GridManager::grid[tx - 1][ty + 1] != EMPTY ||
						GridManager::grid[tx - 1][ty - 1] != EMPTY)
					{
						tx = rand() % (X_SIZE - 4) + 2;
						ty = rand() % (Y_SIZE - 2) + 1;
					}
					PushBackObject(new Trash(tx, ty, tstate));
					i++;
				}

				for (int i = 0; i < 1;)
				{
					int tx = rand() % (X_SIZE - 4) + 2;
					int ty = rand() % (Y_SIZE - 2) + 1;
					int tstate = rand() % 4 + 1;

					while (GridManager::grid[tx][ty] != EMPTY ||
						GridManager::grid[tx + 1][ty] != EMPTY ||
						GridManager::grid[tx - 1][ty] != EMPTY ||
						GridManager::grid[tx][ty + 1] != EMPTY ||
						GridManager::grid[tx][ty - 1] != EMPTY ||
						GridManager::grid[tx + 1][ty + 1] != EMPTY ||
						GridManager::grid[tx + 1][ty - 1] != EMPTY ||
						GridManager::grid[tx - 1][ty + 1] != EMPTY ||
						GridManager::grid[tx - 1][ty - 1] != EMPTY)
					{
						tx = rand() % (X_SIZE - 4) + 2;
						ty = rand() % (Y_SIZE - 2) + 1;
					}
					PushBackObject(new Food(tx, ty, tstate));
					i++;
				}

				for (int i = 0; i < 4;)
				{
					int tx = rand() % (X_SIZE - 4) + 2;
					int ty = rand() % (Y_SIZE - 2) + 1;
					int tstate = rand() % 2 + 1;

					while (GridManager::grid[tx][ty] != EMPTY ||
						GridManager::grid[tx + 1][ty] != EMPTY ||
						GridManager::grid[tx - 1][ty] != EMPTY ||
						GridManager::grid[tx][ty + 1] != EMPTY ||
						GridManager::grid[tx][ty - 1] != EMPTY ||
						GridManager::grid[tx + 1][ty + 1] != EMPTY ||
						GridManager::grid[tx + 1][ty - 1] != EMPTY ||
						GridManager::grid[tx - 1][ty + 1] != EMPTY ||
						GridManager::grid[tx - 1][ty - 1] != EMPTY)
					{
						tx = rand() % (X_SIZE - 4) + 2;
						ty = rand() % (Y_SIZE - 2) + 1;
					}
					PushBackObject(new Build(tx, ty, tstate));
					i++;

				}

				for (int i = 0; i < 3;)
				{
					int tx = rand() % (X_SIZE - 6) + 3;
					int ty = rand() % (Y_SIZE - 2) + 1;

					while (GridManager::grid[tx][ty] != EMPTY ||
						GridManager::grid[tx + 1][ty] != EMPTY ||
						GridManager::grid[tx - 1][ty] != EMPTY ||
						GridManager::grid[tx][ty + 1] != EMPTY ||
						GridManager::grid[tx][ty - 1] != EMPTY ||
						GridManager::grid[tx + 1][ty + 1] != EMPTY ||
						GridManager::grid[tx + 1][ty - 1] != EMPTY ||
						GridManager::grid[tx - 1][ty + 1] != EMPTY ||
						GridManager::grid[tx - 1][ty - 1] != EMPTY)
					{
						tx = rand() % (X_SIZE - 6) + 3;
						ty = rand() % (Y_SIZE - 2) + 1;
					}
					PushBackObject(new FootPrint(tx, ty));
					i++;

				}
			}
			else if (DayManager::dayCount == 3)
			{
				for (int i = 0; i < 4;)
				{
					int tx = rand() % (X_SIZE - 4) + 2;
					int ty = rand() % (Y_SIZE - 2) + 1;
					int tstate = 5;

					while (GridManager::grid[tx][ty] != EMPTY ||
						GridManager::grid[tx + 1][ty] != EMPTY ||
						GridManager::grid[tx - 1][ty] != EMPTY ||
						GridManager::grid[tx][ty + 1] != EMPTY ||
						GridManager::grid[tx][ty - 1] != EMPTY ||
						GridManager::grid[tx + 1][ty + 1] != EMPTY ||
						GridManager::grid[tx + 1][ty - 1] != EMPTY ||
						GridManager::grid[tx - 1][ty + 1] != EMPTY ||
						GridManager::grid[tx - 1][ty - 1] != EMPTY)
					{
						tx = rand() % (X_SIZE - 4) + 2;
						ty = rand() % (Y_SIZE - 2) + 1;
					}
					PushBackObject(new Food(tx, ty, tstate));
					i++;

				}
				for (int i = 0; i < 3;)
				{
					int tx = rand() % (X_SIZE - 4) + 2;
					int ty = rand() % (Y_SIZE - 2) + 1;

					while (GridManager::grid[tx][ty] != EMPTY ||
						GridManager::grid[tx + 1][ty] != EMPTY ||
						GridManager::grid[tx - 1][ty] != EMPTY ||
						GridManager::grid[tx][ty + 1] != EMPTY ||
						GridManager::grid[tx][ty - 1] != EMPTY ||
						GridManager::grid[tx + 1][ty + 1] != EMPTY ||
						GridManager::grid[tx + 1][ty - 1] != EMPTY ||
						GridManager::grid[tx - 1][ty + 1] != EMPTY ||
						GridManager::grid[tx - 1][ty - 1] != EMPTY)
					{
						tx = rand() % (X_SIZE - 4) + 2;
						ty = rand() % (Y_SIZE - 2) + 1;
					}
					PushBackObject(new Water(tx, ty));
					i++;
				}

				for (int i = 0; i < 1;)
				{
					int tx = rand() % (X_SIZE - 4) + 2;
					int ty = rand() % (Y_SIZE - 2) + 1;
					int tstate = rand() % 4 + 1;

					while (GridManager::grid[tx][ty] != EMPTY ||
						GridManager::grid[tx + 1][ty] != EMPTY ||
						GridManager::grid[tx - 1][ty] != EMPTY ||
						GridManager::grid[tx][ty + 1] != EMPTY ||
						GridManager::grid[tx][ty - 1] != EMPTY ||
						GridManager::grid[tx + 1][ty + 1] != EMPTY ||
						GridManager::grid[tx + 1][ty - 1] != EMPTY ||
						GridManager::grid[tx - 1][ty + 1] != EMPTY ||
						GridManager::grid[tx - 1][ty - 1] != EMPTY)
					{
						tx = rand() % (X_SIZE - 4) + 2;
						ty = rand() % (Y_SIZE - 2) + 1;
					}
					PushBackObject(new Food(tx, ty, tstate));
					i++;
				}

				for (int i = 0; i < 1;)
				{
					int tx = rand() % (X_SIZE - 4) + 2;
					int ty = rand() % (Y_SIZE - 2) + 1;
					int tstate = rand() % 3 + 1;

					while (GridManager::grid[tx][ty] != EMPTY ||
						GridManager::grid[tx + 1][ty] != EMPTY ||
						GridManager::grid[tx - 1][ty] != EMPTY ||
						GridManager::grid[tx][ty + 1] != EMPTY ||
						GridManager::grid[tx][ty - 1] != EMPTY ||
						GridManager::grid[tx + 1][ty + 1] != EMPTY ||
						GridManager::grid[tx + 1][ty - 1] != EMPTY ||
						GridManager::grid[tx - 1][ty + 1] != EMPTY ||
						GridManager::grid[tx - 1][ty - 1] != EMPTY)
					{
						tx = rand() % (X_SIZE - 4) + 2;
						ty = rand() % (Y_SIZE - 2) + 1;
					}
					PushBackObject(new Trash(tx, ty, tstate));
					i++;
				}

				for (int i = 0; i < 4;)
				{
					int tx = rand() % (X_SIZE - 4) + 2;
					int ty = rand() % (Y_SIZE - 2) + 1;
					int tstate = rand() % 2 + 1;

					while (GridManager::grid[tx][ty] != EMPTY ||
						GridManager::grid[tx + 1][ty] != EMPTY ||
						GridManager::grid[tx - 1][ty] != EMPTY ||
						GridManager::grid[tx][ty + 1] != EMPTY ||
						GridManager::grid[tx][ty - 1] != EMPTY ||
						GridManager::grid[tx + 1][ty + 1] != EMPTY ||
						GridManager::grid[tx + 1][ty - 1] != EMPTY ||
						GridManager::grid[tx - 1][ty + 1] != EMPTY ||
						GridManager::grid[tx - 1][ty - 1] != EMPTY)
					{
						tx = rand() % (X_SIZE - 4) + 2;
						ty = rand() % (Y_SIZE - 2) + 1;
					}
					PushBackObject(new Build(tx, ty, tstate));
					i++;
				}
			}
			else if (DayManager::dayCount == 4)
			{
				for (int i = 0; i < 4;)
				{
					int tx = rand() % (X_SIZE - 4) + 2;
					int ty = rand() % (Y_SIZE - 2) + 1;

					while (GridManager::grid[tx][ty] != EMPTY ||
						GridManager::grid[tx + 1][ty] != EMPTY ||
						GridManager::grid[tx - 1][ty] != EMPTY ||
						GridManager::grid[tx][ty + 1] != EMPTY ||
						GridManager::grid[tx][ty - 1] != EMPTY ||
						GridManager::grid[tx + 1][ty + 1] != EMPTY ||
						GridManager::grid[tx + 1][ty - 1] != EMPTY ||
						GridManager::grid[tx - 1][ty + 1] != EMPTY ||
						GridManager::grid[tx - 1][ty - 1] != EMPTY)
					{
						tx = rand() % (X_SIZE - 4) + 2;
						ty = rand() % (Y_SIZE - 2) + 1;
					}
					PushBackObject(new Water(tx, ty));
					i++;
				}

				for (int i = 0; i < 3;)
				{
					int tx = rand() % (X_SIZE - 4) + 2;
					int ty = rand() % (Y_SIZE - 2) + 1;
					int tstate = rand() % 3 + 1;

					while (GridManager::grid[tx][ty] != EMPTY ||
						GridManager::grid[tx + 1][ty] != EMPTY ||
						GridManager::grid[tx - 1][ty] != EMPTY ||
						GridManager::grid[tx][ty + 1] != EMPTY ||
						GridManager::grid[tx][ty - 1] != EMPTY ||
						GridManager::grid[tx + 1][ty + 1] != EMPTY ||
						GridManager::grid[tx + 1][ty - 1] != EMPTY ||
						GridManager::grid[tx - 1][ty + 1] != EMPTY ||
						GridManager::grid[tx - 1][ty - 1] != EMPTY)
					{
						tx = rand() % (X_SIZE - 4) + 2;
						ty = rand() % (Y_SIZE - 2) + 1;
					}
					PushBackObject(new Trash(tx, ty, tstate));
					i++;
				}

				for (int i = 0; i < 3;)
				{
					int tx = rand() % (X_SIZE - 4) + 2;
					int ty = rand() % (Y_SIZE - 2) + 1;
					int tstate = rand() % 2 + 1;

					while (GridManager::grid[tx][ty] != EMPTY ||
						GridManager::grid[tx + 1][ty] != EMPTY ||
						GridManager::grid[tx - 1][ty] != EMPTY ||
						GridManager::grid[tx][ty + 1] != EMPTY ||
						GridManager::grid[tx][ty - 1] != EMPTY ||
						GridManager::grid[tx + 1][ty + 1] != EMPTY ||
						GridManager::grid[tx + 1][ty - 1] != EMPTY ||
						GridManager::grid[tx - 1][ty + 1] != EMPTY ||
						GridManager::grid[tx - 1][ty - 1] != EMPTY)
					{
						tx = rand() % (X_SIZE - 4) + 2;
						ty = rand() % (Y_SIZE - 2) + 1;
					}
					PushBackObject(new Build(tx, ty, tstate));
					i++;

				}
			}
			frameCount = 0;
		}
	}
	*/

	if (isGenerate)
	{
		frameCount++;
		if (frameCount >= 100)
		{
			for (auto& i : buildList)
				Destroy(i);
			for (auto& i : bushList)
				Destroy(i);
			for (auto& i : foodList)
				Destroy(i);
			for (auto& i : trashList)
				Destroy(i);
			for (auto& i : waterList)
				Destroy(i);

			if (main == 1)
			{
				for (int s = 0; s < 3; s++)
				{
				}
			}
			else if (main == 2)
			{

			}
			else if (main == 3)
			{

			}
			else if (main == 4)
			{

			}
		}
	}

	for (auto& i : waterList)
	{
		if (i->transform->scale.x <= 0)
		{
			Destroy(i);
		}
	}

}

void ObjectManager::LateUpdate()
{
	Remove();
}

void ObjectManager::GenerateObjects(int main, int sub1, int sub2, int sub3)
{
	isGenerate = true;
	this->main = main;
	sub[0] = sub1;
	sub[1] = sub2;
	sub[2] = sub3;
}

void ObjectManager::Remove()
{
	for (auto& i : buildDestroyed)
	{
		buildList.remove(i);
		Scene::GetCurrentScene().Destroy(i);
	}
	buildDestroyed.clear();

	for (auto& i : bushDestroyed)
	{
		bushList.remove(i);
		Scene::GetCurrentScene().Destroy(i);
	}
	bushDestroyed.clear();

	for (auto& i : foodDestroyed)
	{
		foodList.remove(i);
		Scene::GetCurrentScene().Destroy(i);
	}
	foodDestroyed.clear();

	for (auto& i : footPrintDestroyed)
	{
		footPrintList.remove(i);
		Scene::GetCurrentScene().Destroy(i);
	}
	foodDestroyed.clear();

	for (auto& i : stoneDestroyed)
	{
		stoneList.remove(i);
		Scene::GetCurrentScene().Destroy(i);
	}
	stoneDestroyed.clear();

	for (auto& i : trashDestroyed)
	{
		trashList.remove(i);
		Scene::GetCurrentScene().Destroy(i);
	}
	trashDestroyed.clear();

	for (auto& i : waterDestroyed)
	{
		waterList.remove(i);
		Scene::GetCurrentScene().Destroy(i);
	}
	waterDestroyed.clear();
}

wchar_t* ObjectManager::GetLocation(int x, int y)
{
	wchar_t* result = (wchar_t*)L"";

	if (x <= 74 && y <= 87)
		result = (wchar_t*)L"숲 근처";
	if (x <= 74 && y >= 88)
		result = (wchar_t*)L"연못 근처";
	if (x >= 75 && x <= 151 && y <= 24)
		result = (wchar_t*)L"창고";
	if (x >= 75 && x <= 151 && y >= 25 && y <= 81)
		result = (wchar_t*)L"공터";
	if (x >= 75 && x <= 151 && y >= 82)
		result = (wchar_t*)L"초원";
	if (x >= 152 && y <= 66)
		result = (wchar_t*)L"도랑 근처 공터";
	if (x >= 152 && y >= 67)
		result = (wchar_t*)L"도로변";

	return result;
}

void ObjectManager::GenerateObstacle(int state)
{
	bool isEmpty = false;
	int x, y;
	while (!isEmpty)
	{
		isEmpty = true;
		x = rand() % (X_SIZE - 14) + 7;
		y = rand() % (Y_SIZE - 10) + 5;
		
		for (int i = x - 7; i <= x + 7; i++)
		{
			for (int j = y - 5; j <= y + 5; j++)
			{
				if (GridManager::grid[i][j] != Grid::EMPTY)
				{
					isEmpty = false;
					break;
				}
			}
		}
	}

	PushBackObject(new Stone(x, y, state));
}

void ObjectManager::GenerateBuild(int state)
{
	bool isEmpty = false;
	int x, y;
	while (!isEmpty)
	{
		isEmpty = true;
		x = rand() % (X_SIZE - 4) + 2;
		y = rand() % (Y_SIZE - 2) + 1;

		for (int i = x - 2; i <= x + 2; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				if (GridManager::grid[i][j] != Grid::EMPTY)
				{
					isEmpty = false;
					break;
				}
			}
		}
	}

	PushBackObject(new Build(x, y, state));
}

void ObjectManager::GenerateFood(int state)
{
	bool isEmpty = false;
	int x, y;
	while (!isEmpty)
	{
		isEmpty = true;
		x = rand() % (X_SIZE - 4) + 2;
		y = rand() % (Y_SIZE - 2) + 1;

		for (int i = x - 2; i <= x + 2; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				if (GridManager::grid[i][j] != Grid::EMPTY)
				{
					isEmpty = false;
					break;
				}
			}
		}
	}

	PushBackObject(new Food(x, y, state));
}

void ObjectManager::GenerateTrash(int state)
{
	bool isEmpty = false;
	int x, y;
	while (!isEmpty)
	{
		isEmpty = true;
		x = rand() % (X_SIZE - 4) + 2;
		y = rand() % (Y_SIZE - 2) + 1;

		for (int i = x - 2; i <= x + 2; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				if (GridManager::grid[i][j] != Grid::EMPTY)
				{
					isEmpty = false;
					break;
				}
			}
		}
	}

	PushBackObject(new Trash(x, y, state));
}

void ObjectManager::GenerateWater()
{
	bool isEmpty = false;
	int x, y;
	while (!isEmpty)
	{
		isEmpty = true;
		x = rand() % (X_SIZE - 4) + 2;
		y = rand() % (Y_SIZE - 2) + 1;

		for (int i = x - 2; i <= x + 2; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				if (GridManager::grid[i][j] != Grid::EMPTY)
				{
					isEmpty = false;
					break;
				}
			}
		}
	}

	PushBackObject(new Water(x, y));
}
