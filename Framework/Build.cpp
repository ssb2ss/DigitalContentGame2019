#include "stdafx.h"
#include "Build.h"
#include "GridManager.h"
#include "Scene.h"
#include "GameManager.h"


Build::Build(int x, int y, int state) :
	GameObject(L"resources/sprites/leaf.png", GameManager::GetInstance()->GetGridPos(x, y)), x(x), y(y), state(state)
{
	if (state == 1)
		ChangeSprite(L"resources/sprites/leaf.png");
	else if (state == 2)
		ChangeSprite(L"resources/sprites/wood.png");

	transform->SetScale(0.8f, 0.8f);

	SetGrid();
}

Build::~Build()
{
	if (state == 1)
	{
		for (int i = x - 4; i <= x + 3; i++)
		{
			if (i <= x - 3 || i == x + 3)
			{
				GridManager::grid[i][y] = Grid::EMPTY;
				GridManager::grid[i][y + 1] = Grid::EMPTY;
			}
			else
			{
				for (int j = y - 1; j <= y + 1; j++)
				{
					GridManager::grid[i][j] = Grid::EMPTY;
				}
			}
		}
	}
	else if (state == 2)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			GridManager::grid[i][y] = Grid::EMPTY;
		}
	}
}

void Build::SetGrid()
{
	if (state == 1)
	{
		for (int i = x - 4; i <= x + 3; i++)
		{
			if (i <= x - 3 || i == x + 3)
			{
				GridManager::grid[i][y] = Grid::BUILD_1;
				GridManager::grid[i][y + 1] = Grid::BUILD_1;
			}
			else
			{
				for (int j = y - 1; j <= y + 1; j++)
				{
					GridManager::grid[i][j] = Grid::BUILD_1;
				}
			}
		}
	}
	else if (state == 2)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			GridManager::grid[i][y] = Grid::BUILD_2;
		}
	}
}

void Build::ChangeSprite(const wchar_t* path)
{
	SAFE_DELETE(renderer);
	renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(path, 0, 0));
}
