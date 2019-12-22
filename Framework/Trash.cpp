#include "stdafx.h"
#include "Trash.h"
#include "InputManager.h"
#include "GridManager.h"
#include "Scene.h"
#include "GameManager.h"


Trash::Trash(int x, int y, int state) :
	GameObject(L"resources/sprites/tissue.png", GameManager::GetInstance()->GetGridPos(x, y)), x(x), y(y), state(state)
{
	if (state == TrashEnum::TISSUE)
		ChangeSprite(L"resources/sprites/tissue.png");
	else if (state == TrashEnum::BOTTLE)
		ChangeSprite(L"resources/sprites/bottle.png");
	else if (state == TrashEnum::CAN)
		ChangeSprite(L"resources/sprites/can.png");
	else if (state == TrashEnum::MASK)
		ChangeSprite(L"resources/sprites/mask.png");

	transform->SetScale(0.7f, 0.7f);

	SetGrid();
}

Trash::~Trash()
{
	if (state == 1)
	{
		GridManager::grid[x][y] = Grid::EMPTY;
	}
	else if (state == 2)
	{
		for (int i = x - 2; i <= x + 2; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::EMPTY;
			}
		}
	}
	else if (state == 3)
	{
		for (int i = x - 2; i <= x + 2; i++)
		{
			if (i <= x)
			{
				for (int j = y - 1; j <= y; j++)
				{
					GridManager::grid[i][j] = Grid::EMPTY;
				}
			}
			else if (i == x + 1)
			{
				for (int j = y - 1; j <= y + 1; j++)
				{
					GridManager::grid[i][j] = Grid::EMPTY;
				}
			}
			else
			{
				GridManager::grid[i][y + 1] = Grid::EMPTY;
			}
		}
	}
}

void Trash::SetGrid()
{
	if (state == 1)
	{
		GridManager::grid[x][y] = Grid::TRASH_1;
	}
	else if (state == 2)
	{
		for (int i = x - 2; i <= x + 2; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::TRASH_2;
			}
		}
	}
	else if (state == 3)
	{
		for (int i = x - 2; i <= x + 2; i++)
		{
			if (i <= x)
			{
				for (int j = y - 1; j <= y; j++)
				{
					GridManager::grid[i][j] = Grid::TRASH_3;
				}
			}
			else if (i == x + 1)
			{
				for (int j = y - 1; j <= y + 1; j++)
				{
					GridManager::grid[i][j] = Grid::TRASH_3;
				}
			}
			else
			{
				GridManager::grid[i][y + 1] = Grid::TRASH_3;
			}
		}
	}
}

void Trash::ChangeSprite(const wchar_t* path)
{
	SAFE_DELETE(renderer);
	renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(path, 0, 0));
}
