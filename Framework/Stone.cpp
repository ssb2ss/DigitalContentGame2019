#include "stdafx.h"
#include "Stone.h"
#include "GridManager.h"
#include "GameManager.h"


Stone::Stone(int x, int y, bool isBlack) :
	GameObject((isBlack) ? L"resources/sprites/stone_1.png" : L"resources/sprites/stone_2.png", GameManager::GetInstance()->GetGridPos(x, y)), x(x), y(y)
{
	transform->SetScale(0.8f, 0.8f);

	for (int i = x - 3; i <= x + 2; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			GridManager::grid[i][j] = Grid::OBSTACLE;
		}
		if (i >= x - 2 && i <= x + 1)
		{
			GridManager::grid[i][y - 2] = Grid::OBSTACLE;
		}
	}
}

Stone::~Stone()
{
	for (int i = x - 3; i <= x + 2; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			GridManager::grid[i][j] = Grid::EMPTY;
		}
		if (i >= x - 2 && i <= x + 1)
		{
			GridManager::grid[i][y - 2] = Grid::EMPTY;
		}
	}
}
