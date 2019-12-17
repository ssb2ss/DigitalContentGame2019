#include "stdafx.h"
#include "ObjectManager.h"
#include "Scene.h"
#include "GridManager.h"



ObjectManager::ObjectManager()
{
	dayCheck = DayManager::dayCount - 1;
	frameCount = 0;
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
					//int tstate = rand() % 4 + 1;
					int tstate = 4;

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
