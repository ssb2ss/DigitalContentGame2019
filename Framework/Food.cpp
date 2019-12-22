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
	else if (state == FoodEnum::CHICKEN)
		ChangeSprite(L"resources/sprites/chicken.png");
	else if (state == FoodEnum::CARROT)
		ChangeSprite(L"resources/sprites/carrot.png");
	else if (state == FoodEnum::POPCORN)
		ChangeSprite(L"resources/sprites/popcorn.png");
	else if (state == FoodEnum::FISH)
		ChangeSprite(L"resources/sprites/fish.png");
	else if (state == FoodEnum::COTTONCANDY)
		ChangeSprite(L"resources/sprites/cottoncandy.png");
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
	else if (state == FoodEnum::CHICKEN)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::EMPTY;
			}
		}
	}
	else if (state == FoodEnum::CARROT)
	{
		for (int i = x - 2; i <= x + 2; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::EMPTY;
			}
		}
	}
	else if (state == FoodEnum::POPCORN)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			for (int j = y - 3; j <= y + 3; j++)
			{
				GridManager::grid[i][j] = Grid::EMPTY;
			}
		}
	}
	else if (state == FoodEnum::FISH)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			for (int j = y - 2; j <= y + 2; j++)
			{
				GridManager::grid[i][j] = Grid::EMPTY;
			}
		}
	}
	else if (state == FoodEnum::COTTONCANDY)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			for (int j = y - 1; j <= y + 2; j++)
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
	if (state == FoodEnum::CHICKEN)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::FOOD_5;
			}
		}
	}
	else if (state == FoodEnum::CARROT)
	{
		for (int i = x - 2; i <= x + 2; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::FOOD_6;
			}
		}
	}
	 if (state == FoodEnum::POPCORN)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			for (int j = y - 3; j <= y + 3; j++)
			{
				GridManager::grid[i][j] = Grid::FOOD_7;
			}
		}
	}
	 if (state == FoodEnum::FISH)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			for (int j = y - 2; j <= y + 2; j++)
			{
				GridManager::grid[i][j] = Grid::FOOD_8;
			}
		}
	}
	 if (state == FoodEnum::COTTONCANDY)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			for (int j = y - 1; j <= y + 2; j++)
			{
				GridManager::grid[i][j] = Grid::FOOD_8;
			}
		}
	}
	else if (state == FoodEnum::GRASSHOPPER)
	{
		for (int i = x - 1; i <= x + 2; i++)
		{
			GridManager::grid[i][y] = Grid::FOOD_9;
		}
	}
}

void Food::ChangeSprite(const wchar_t* path)
{
	SAFE_DELETE(renderer);
	renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(path, 0, 0));
}

