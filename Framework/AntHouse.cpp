#include "stdafx.h"
#include "AntHouse.h"
#include "GridManager.h"
#include "Scene.h"

AntHouse::AntHouse(int x, int y, AntManager* antManager) :
	GameObject(L"resources/sprites/house_1.png", Vector2(52 + x * GRID_SIZE, 56 + y * GRID_SIZE)), x(x), y(y), level(1), am(antManager), timeSave(0)
{
	transform->SetScale(0.8f, 0.8f);
	renderer->SetLayer(0);

	SetGrid();

	for (int i = x - 3; i <= x + 3; i += 2)
		am->PushBackAnt(new Ant(i, y + 2));
}

AntHouse::~AntHouse()
{

}

void AntHouse::SetLevel(int l)
{
	level = l;
	if (level == 1)
	{
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/house_1.png", 0, 0));
		renderer->SetLayer(1);
	}
	else if (level == 2)
	{
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/house_2.png", 0, 0));
		renderer->SetLayer(1);
	}
	else if (level == 3)
	{
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/house_3.png", 0, 0));
		renderer->SetLayer(1);
	}
	else if (level == 4)
	{
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/house_4.png", 0, 0));
		renderer->SetLayer(1);
	}
	SetGrid();
}

int AntHouse::GetLevel()
{
	return level;
}

void AntHouse::GenerateAnt()
{
	timeSave += TimeManager::GetDeltaTime();
	if (timeSave >= 60)
	{
		for (int i = x - 3; i <= x + 3; i += 2)
			am->PushBackAnt(new Ant(i, y + 2));
		timeSave = 0;
	}

}

void AntHouse::Update()
{
	GenerateAnt();
}


void AntHouse::SetGrid()
{
	if (level == 1)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			if ((i >= x - 3 && i <= x - 2) || (i >= x + 2 && i <= x + 3))
			{
				GridManager::grid[i][y + 1] = Grid::HOUSE;
			}
			else
			{
				for (int j = y - 2; j <= y + 1; j++)
				{
					GridManager::grid[i][j] = Grid::HOUSE;
				}
			}
		}
	}
	else if(level == 2)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			if (i == x - 3 || i == x + 3)
			{
				GridManager::grid[i][y + 1] = Grid::HOUSE;
			}
			else if (i == x - 2 || i == x + 2)
			{
				GridManager::grid[i][y] = Grid::HOUSE;
				GridManager::grid[i][y + 1] = Grid::HOUSE;
			}
			else
			{
				for (int j = y - 2; j <= y + 1; j++)
				{
					GridManager::grid[i][j] = Grid::HOUSE;
				}
			}
		}
	}
	else if (level == 3)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			if (i == x - 3 || i == x + 3)
			{
				GridManager::grid[i][y + 1] = Grid::HOUSE;
			}
			else if (i >= x + 1 && i <= x + 2)
			{
				GridManager::grid[i][y] = Grid::HOUSE;
				GridManager::grid[i][y + 1] = Grid::HOUSE;
			}
			else if (i == x - 2)
			{
				for (int j = y - 1; j <= y + 1; j++)
				{
					GridManager::grid[i][j] = Grid::HOUSE;
				}
			}
			else
			{
				for (int j = y - 2; j <= y + 1; j++)
				{
					GridManager::grid[i][j] = Grid::HOUSE;
				}
			}
		}
	}
	else if (level == 4)
	{
		for (int i = x - 5; i <= x + 5; i++)
		{
			if (i == x - 5 || i == x + 5)
			{
				GridManager::grid[i][y + 2] = Grid::HOUSE;
			}
			else if (i == x - 4 || i == x + 4)
			{
				GridManager::grid[i][y + 1] = Grid::HOUSE;
				GridManager::grid[i][y + 2] = Grid::HOUSE;
			}
			else if ((i >= x - 3 && i <= x - 2) || (i >= x + 2 && i <= x + 3))
			{
				for (int j = y; j <= y + 2; j++)
				{
					GridManager::grid[i][j] = Grid::HOUSE;
				}
			}
			else if (i == x - 1)
			{
				for (int j = y - 1; j <= y + 2; j++)
				{
					GridManager::grid[i][j] = Grid::HOUSE;
				}
			}
			else
			{
				for (int j = y - 2; j <= y + 2; j++)
				{
					GridManager::grid[i][j] = Grid::HOUSE;
				}
			}
		}
	}
}
