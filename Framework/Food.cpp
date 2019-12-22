#include "stdafx.h"
#include "Food.h"
#include "GridManager.h"
#include "Scene.h"
#include "GameManager.h"

Food::Food(int x, int y, int state) :
	GameObject(L"resources/sprites/bread.png", GameManager::GetInstance()->GetGridPos(x, y)), x(x), y(y), state(state)
{
	if (state == FoodEnum::BREAD)
		ChangeSprite(L"resources/sprites/bread.png");
	else if (state == FoodEnum::ICECREAM)
		ChangeSprite(L"resources/sprites/icecream.png");
	else if (state == FoodEnum::SNACK)
		ChangeSprite(L"resources/sprites/snack.png");
	else if (state == FoodEnum::PIZZA)
		ChangeSprite(L"resources/sprites/pizza.png");
	else if (state == FoodEnum::GRASSHOPPER)
		ChangeSprite(L"resources/sprites/grasshopper.png");

	transform->SetScale(0.7f, 0.7f);

	SetGrid();
}


Food::~Food()
{
	if (state == FoodEnum::BREAD)
	{
		for (int i = x - 1; i <= x + 1; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::EMPTY;
			}
		}
	}
	else if (state == FoodEnum::ICECREAM)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			GridManager::grid[x][j] = Grid::EMPTY;
		}
	}
	else if (state == FoodEnum::SNACK)
	{
		GridManager::grid[x][y] = Grid::EMPTY;
	}
	else if (state == FoodEnum::PIZZA)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			for (int j = y - 2; j <= y + 2; j++)
			{
				GridManager::grid[i][j] = Grid::EMPTY;
			}
		}
	}
	else if (state == FoodEnum::GRASSHOPPER)
	{
		for (int i = x - 1; i <= x + 2; i++)
		{
			GridManager::grid[i][y] = Grid::EMPTY;
		}
	}
}

void Food::SetGrid()
{
	if (state == FoodEnum::BREAD)
	{
		for (int i = x - 1; i <= x + 1; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::FOOD_1;
			}
		}
	}
	else if (state == FoodEnum::ICECREAM)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			GridManager::grid[x][j] = Grid::FOOD_2;
		}
	}
	else if (state == FoodEnum::SNACK)
	{
		GridManager::grid[x][y] = Grid::FOOD_3;
	}
	else if (state == FoodEnum::PIZZA)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			for (int j = y - 2; j <= y + 2; j++)
			{
				GridManager::grid[i][j] = Grid::FOOD_4;
			}
		}
	}
	else if (state == FoodEnum::GRASSHOPPER)
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

