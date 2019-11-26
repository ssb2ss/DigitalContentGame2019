#include "stdafx.h"
#include "Food.h"
#include "GridManager.h"
#include "Scene.h"

//积己 : 全己格
//荐沥 : 辫柳快

Food::Food(int x, int y, int state) :
	GameObject(L"resources/sprites/bread.png", Vector2(52 + x * GRID_SIZE, 56 + y * GRID_SIZE)), x(x), y(y), state(state)
{
	if (state == 1)
		ChangeSprite(L"resources/sprites/bread.png");
	else if (state == 2)
		ChangeSprite(L"resources/sprites/icecream.png");
	else if (state == 3)
		ChangeSprite(L"resources/sprites/snack.png");
	else if (state == 4)
		ChangeSprite(L"resources/sprites/banana.png");
	else if (state == 5)
		ChangeSprite(L"resources/sprites/grasshopper.png");

	transform->SetScale(0.7f, 0.7f);

	SetGrid();
}


Food::~Food()
{
	if (state == 1)
	{
		for (int i = x - 1; i <= x + 1; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::EMPTY;
			}
		}
	}
	else if (state == 2)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			GridManager::grid[x][j] = Grid::EMPTY;
		}
	}
	else if (state == 3)
	{
		GridManager::grid[x][y] = Grid::EMPTY;
	}
	else if (state == 4)
	{
		for (int i = x - 1; i <= x + 1; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::EMPTY;
			}
		}
	}
	else if (state == 5)
	{
		for (int i = x - 1; i <= x + 2; i++)
		{
			GridManager::grid[i][y] = Grid::EMPTY;
		}
	}
}

void Food::SetGrid()
{
	if (state == 1)
	{
		for (int i = x - 1; i <= x + 1; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::FOOD_1;
			}
		}
	}
	else if (state == 2)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			GridManager::grid[x][j] = Grid::FOOD_2;
		}
	}
	else if (state == 3)
	{
		GridManager::grid[x][y] = Grid::FOOD_3;
	}
	else if (state == 4)
	{
		for (int i = x - 1; i <= x + 1; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::FOOD_4;
			}
		}
	}
	else if (state == 5)
	{
		for (int i = x - 1; i <= x + 2; i++)
		{
			GridManager::grid[i][y] = Grid::FOOD_5;
		}
	}
}

void Food::ChangeSprite(const wchar_t* path)
{
	SAFE_DELETE(renderer);
	renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(path, 0, 0));
}

