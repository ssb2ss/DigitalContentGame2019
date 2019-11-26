#include "stdafx.h"
#include "Water.h"
#include "GridManager.h"

//积己 : 全己格

Water::Water(int x, int y) :
	GameObject(L"resources/sprites/water.png", Vector2(52 + x * GRID_SIZE, 56 + y * GRID_SIZE)), x(x), y(y), isDestroy(false)
{
	transform->SetScale(0.8f, 0.8f);

	for (int i = x - 2; i <= x + 2; i++)
	{
		if (i != x + 2)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::WATER;
			}
		}
		else
		{
			for (int j = y - 1; j <= y; j++)
			{
				GridManager::grid[i][j] = Grid::WATER;
			}
		}
	}
}

Water::~Water()
{
	for (int i = x - 2; i <= x + 2; i++)
	{
		if (i != x + 2)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::EMPTY;
			}
		}
		else
		{
			for (int j = y - 1; j <= y; j++)
			{
				GridManager::grid[i][j] = Grid::EMPTY;
			}
		}
	}
}

void Water::Update()
{
	if (isDestroy)
	{
		transform->SetScale(transform->scale.x - 0.05f, transform->scale.y - 0.05f);
	}
}
