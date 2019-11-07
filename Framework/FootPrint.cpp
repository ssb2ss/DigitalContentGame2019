#include "stdafx.h"
#include "FootPrint.h"
#include "GridManager.h"

FootPrint::FootPrint(int x, int y) :
	GameObject(L"resources/sprites/foot.png", Vector2(52 + x * GRID_SIZE, 56 + y * GRID_SIZE)), x(x), y(y)
{
	transform->SetScale(1.2f, 1.2f);
	transform->SetRotation(110.f);
	renderer->SetAlpha(0.7f);

	for (int i = x - 3; i <= x + 3; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			GridManager::grid[i][j] = Grid::OBSTACLE;
		}
	}
}

FootPrint::~FootPrint()
{
	for (int i = x - 3; i <= x + 3; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			GridManager::grid[i][j] = Grid::EMPTY;
		}
	}
}