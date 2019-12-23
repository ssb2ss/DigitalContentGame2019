#include "stdafx.h"
#include "ObjectManager.h"
#include "Scene.h"
#include "GridManager.h"
#include "GameManager.h"


ObjectManager::ObjectManager()
{
	frameCount = 0;
	timeCount = 0;

	isGenerate = false;
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

AntHouse * ObjectManager::PushBackObject(AntHouse * a)
{
	Scene::GetCurrentScene().PushBackGameObject(a);
	antHouseList.push_back(a);
	return a;
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

void ObjectManager::Destroy(AntHouse * a)
{
	antHouseDestroyed.push_back(a);
}


void ObjectManager::Update()
{

	if (isGenerate)
	{
		frameCount++;
		if (frameCount >= 100 || DayManager::dayCount == 1)
		{
			for (auto& i : buildList)
				Destroy(i);
			for (auto& i : bushList)
				Destroy(i);
			for (auto& i : foodList)
				Destroy(i);
			for (auto& i : stoneList)
				Destroy(i);
			for (auto& i : trashList)
				Destroy(i);
			for (auto& i : waterList)
				Destroy(i);

			if (main == 1)
			{
				for (int s = 0; s < 3; s++)
				{
					switch (sub[s])
					{
					case 0:
						//개미귀신
						for (int i = 0; i < 3; i++)
							GameManager::GetInstance()->enemyManager->GenerateEnemy(0);
						break;
					case 1:
						//창고 음식
						for (int i = 0; i < 5; i++)
						{
							int r = rand() % 3;
							GenerateFood(r);
						}
						break;
					case 2:
						//창고 물
						for (int i = 0; i < 7; i++)
							GenerateWater();
						break;
					case 3:
						//메뚜기
						for (int i = 0; i < 5; i++)
							GenerateFood(FoodEnum::GRASSHOPPER);
						break;
					case 4:
						//야광봉
						for (int i = 0; i < 8; i++)
							GenerateObstacle(ObstacleEnum::LIGHT);
						break;
					case 5:
						//소풍
						for (int i = 0; i < 5; i++)
							GenerateTrash(TrashEnum::LUNCH);
						break;
					case 6:
						//연극
						for (int i = 0; i < 4; i++)
							GenerateObstacle(ObstacleEnum::PERSONA);
						break;
					case 7:
						//과자파티
						for (int i = 0; i < 12; i++)
							GenerateFood(FoodEnum::SNACK);
						break;
					case 8:
						//돌덩이
						for (int i = 0; i < 6; i++)
						{
							int r = rand() % 3;
							if (r == 0)
								GenerateObstacle(ObstacleEnum::STONE_1);
							else if (r == 1)
								GenerateObstacle(ObstacleEnum::STONE_2);
							else if (r == 1)
								GenerateObstacle(ObstacleEnum::STONE_3);
						}
						break;
					case 9:
						//채식주의자 시위
						for (int i = 0; i < 6; i++)
							GenerateFood(FoodEnum::CARROT);
						break;
					case 10:
						//바람
						for (int i = 0; i < 3; i++)
						{
							int r = rand() % 2;
							GenerateBuild(r + 1);
						}
						break;
					}
				}
			}
			else if (main == 2)
			{
				for (int s = 0; s < 3; s++)
				{
					switch (sub[s])
					{
					case 0:
						//개미귀신
						for (int i = 0; i < 3; i++)
							GameManager::GetInstance()->enemyManager->GenerateEnemy(0);
						break;
					case 1:
						//빵
						for (int i = 0; i < 8; i++)
							GenerateFood(FoodEnum::BREAD);
						break;
					case 2:
						//독감(휴지)
						for (int i = 0; i < 8; i++)
							GenerateTrash(TrashEnum::TISSUE);
						break;
					case 3:
						//공사 준비
						for (int i = 0; i < 8; i++)
						{
							int r = rand() % 3;
							if (r == 0)
								GenerateObstacle(ObstacleEnum::STONE_1);
							else if (r == 1)
								GenerateObstacle(ObstacleEnum::STONE_2);
							else if (r == 1)
								GenerateObstacle(ObstacleEnum::STONE_3);
						}
						break;
					case 4:
						//창고 음식
						for (int i = 0; i < 5; i++)
						{
							int r = rand() % 3;
							GenerateFood(r);
						}
						break;
					case 5:
						//창고 물
						for (int i = 0; i < 7; i++)
							GenerateWater();
						break;
					case 6:
						//솜사탕
						for (int i = 0; i < 5; i++)
							GenerateFood(FoodEnum::COTTONCANDY);
						break;
					case 7:
						//낚시
						for (int i = 0; i < 5; i++)
							GenerateFood(FoodEnum::FISH);
						break;
					case 8:
						//야광봉
						for (int i = 0; i < 8; i++)
							GenerateObstacle(ObstacleEnum::LIGHT);
						break;
					case 9:
						//마트 할인
						for (int i = 0; i < 12; i++)
						{
							int r = rand() % 5;
							if (r == 0)
								GenerateFood(FoodEnum::BREAD);
							else if (r == 1)
								GenerateFood(FoodEnum::ICECREAM);
							else if (r == 2)
								GenerateFood(FoodEnum::SNACK);
							else if (r == 3)
								GenerateTrash(TrashEnum::CAN);
							else if (r == 4)
								GenerateTrash(TrashEnum::BOTTLE);
						}
						break;
					case 10:
						//영화
						for (int i = 0; i < 10; i++)
							GenerateFood(FoodEnum::POPCORN);
						break;
					case 11:
						//파스타
						for (int i = 0; i < 5; i++)
							GenerateTrash(TrashEnum::CAN);
						break;
					case 12:
						//나초
						for (int i = 0; i < 12; i++)
							GenerateFood(FoodEnum::SNACK);
						break;
					}
				}
			}
			else if (main == 3)
			{
				for (int s = 0; s < 3; s++)
				{
					switch (sub[s])
					{
					case 0:
						//에어팟
						for (int i = 0; i < 2; i++)
							GenerateObstacle(ObstacleEnum::AIRPOD);
						break;
					case 1:
						//바퀴벌레
						for (int i = 0; i < 3; i++)
							GameManager::GetInstance()->enemyManager->GenerateEnemy(1);
						break;
					case 2:
						//공사 진행
						for (int i = 0; i < 10; i++)
						{
							int r = rand() % 3;
							if (r == 0)
								GenerateObstacle(ObstacleEnum::STONE_1);
							else if (r == 1)
								GenerateObstacle(ObstacleEnum::STONE_2);
							else if (r == 1)
								GenerateObstacle(ObstacleEnum::STONE_3);
						}
						break;
					case 3:
						//공사 파편(돌)
						for (int i = 0; i < 10; i++)
						{
							int r = rand() % 4;
							if (r == 0)
								GenerateObstacle(ObstacleEnum::CONS_ROCK);
							else if (r == 1)
								GenerateObstacle(ObstacleEnum::DUST);
							else if (r == 2)
								GenerateObstacle(ObstacleEnum::BRICK);
							else if (r == 3)
								GenerateBuild(3);
						}
						break;
					case 4:
						//창고 쓰레기
						for (int i = 0; i < 5; i++)
						{
							int r = rand() % 3;
							GenerateTrash(r);
						}
						break;
					case 5:
						//마스크
						for (int i = 0; i < 5; i++)
							GenerateTrash(TrashEnum::MASK);
						break;
					case 6:
						//영화
						for (int i = 0; i < 10; i++)
							GenerateFood(FoodEnum::POPCORN);
						break;
					case 7:
						//공사 반대시위
						for (int i = 0; i < 8; i++)
							GenerateObstacle(ObstacleEnum::POSTER);
						break;
					case 8:
						//파스타
						for (int i = 0; i < 5; i++)
							GenerateTrash(TrashEnum::CAN);
						break;
					case 9:
						//피자
						for (int i = 0; i < 5; i++)
							GenerateFood(FoodEnum::PIZZA);
						break;
					case 10:
						//노점상
						for (int i = 0; i < 6; i++)
							GenerateFood(FoodEnum::CHICKEN);
						break;
					case 11:
						//태풍
						for (int i = 0; i < 6; i++)
						{
							int r = rand() % 2;
							GenerateBuild(r + 1);
						}
						break;
					}
				}
			}
			else if (main == 4)
			{
				for (int s = 0; s < 3; s++)
				{
					switch (sub[s])
					{
					case 0:
						//바퀴벌레
						for (int i = 0; i < 3; i++)
							GameManager::GetInstance()->enemyManager->GenerateEnemy(1);
						break;
					case 1:
						//공사 파편(돌)
						for (int i = 0; i < 10; i++)
						{
							int r = rand() % 4;
							if (r == 0)
								GenerateObstacle(ObstacleEnum::CONS_ROCK);
							else if (r == 1)
								GenerateObstacle(ObstacleEnum::DUST);
							else if (r == 2)
								GenerateObstacle(ObstacleEnum::BRICK);
							else if (r == 3)
								GenerateBuild(3);
						}
						break;
					case 2:
						//공사 쓰레기
						for (int i = 0; i < 12; i++)
						{
							int r = rand() % 4;
							if (r == 0)
								GenerateObstacle(ObstacleEnum::CONS_ROCK);
							else if (r == 1)
								GenerateObstacle(ObstacleEnum::DUST);
							else if (r == 2)
								GenerateObstacle(ObstacleEnum::BRICK);
							else if (r == 3)
								GenerateBuild(3);
						}
						break;
					case 3:
						//창고 쓰레기
						for (int i = 0; i < 5; i++)
						{
							int r = rand() % 3;
							GenerateTrash(r);
						}
						break;
					case 4:
						//음주
						for (int i = 0; i < 7; i++)
							GenerateTrash(TrashEnum::BOTTLE);
						break;
					case 5:
						//아이스크림
						for (int i = 0; i < 7; i++)
							GenerateFood(FoodEnum::ICECREAM);
						break;
					case 6:
						//마스크
						for (int i = 0; i < 6; i++)
							GenerateTrash(TrashEnum::MASK);
						break;
					case 7:
						//태풍
						for (int i = 0; i < 6; i++)
						{
							int r = rand() % 2;
							GenerateBuild(r + 1);
						}
						break;
					}
				}
			}

			for (int i = 0; i < 5; i++)
			{
				int r = rand() % 2;
				GenerateBuild(r + 1);
			}
			GameManager::GetInstance()->enemyManager->GenerateEnemy(rand() % 2);

			frameCount = 0;
			isGenerate = false;
		}
	}

	for (auto& i : waterList)
	{
		if (i->transform->scale.x <= 0)
		{
			Destroy(i);
		}
	}

	timeCount += TimeManager::GetDeltaTime();

	if (timeCount >= 1)
	{
		for (auto& i : antHouseList)
		{
			if (i->isSet)
				if (GridManager::grid[i->x][i->y] != Grid::HOUSE)
					Destroy(i);
		}
		timeCount = 0;
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

	for (auto& i : antHouseDestroyed)
	{
		antHouseList.remove(i);
		Scene::GetCurrentScene().Destroy(i);
	}
	antHouseDestroyed.clear();
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
