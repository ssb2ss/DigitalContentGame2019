#include "stdafx.h"
#include "Bush.h"
#include "GridManager.h"
#include "InputManager.h"



Bush::Bush() : 
	GameObject(L"resources/sprites/bush.png"), x(0), y(0), isSet(false)
{
	transform->SetScale(0.8f, 0.8f);

	renderer->SetAlpha(0.f);
}

Bush::~Bush()
{
	for (int i = x - 4; i <= x + 4; i++)
	{
		if (i <= x + 2)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::EMPTY;
			}
		}
		else
		{
			GridManager::grid[i][y] = Grid::EMPTY;
			GridManager::grid[i][y + 1] = Grid::EMPTY;
		}
	}
}


void Bush::Update()
{
	if (!isSet)
	{
		int mx = InputManager::GetMouseX();
		int my = InputManager::GetMouseY();

		int gx = (mx - 40) / GRID_SIZE;
		int gy = (my - 44) / GRID_SIZE;

		if (gx >= 4 && gx <= X_SIZE - 4 && gy >= 2 && gy <= Y_SIZE - 2)
		{
			x = gx;
			y = gy;

			int temp = true;
			for (int i = x - 4; i <= x + 4; i++)
			{
				if (i <= x + 2)
				{
					for (int j = y - 1; j <= y + 1; j++)
					{
						if (GridManager::grid[i][j] != Grid::EMPTY)
						{
							temp = false;
						}
					}
				}
				else
				{
					if (GridManager::grid[i][y] != Grid::EMPTY || GridManager::grid[i][y + 1] != Grid::EMPTY)
					{
						temp = false;
					}
				}
			}

			if (!temp)
			{
				renderer->SetAlpha(0.2f);
			}
			else
			{
				renderer->SetAlpha(0.6f);
				if (InputManager::GetKeyDown(VK_LBUTTON))
				{
					Setting();
					return;
				}
			}
		}
		else
		{
			renderer->SetAlpha(0.f);
		}

		transform->SetPosition(52 + x * GRID_SIZE, 56 + y * GRID_SIZE);

	}

}

void Bush::Setting()
{
	isSet = true;
	renderer->SetAlpha(0.8f);

	transform->SetPosition(52 + x * GRID_SIZE, 56 + y * GRID_SIZE);

	for (int i = x - 4; i <= x + 4; i++)
	{
		if (i <= x + 2)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::BUSH;
			}
		}
		else
		{
			GridManager::grid[i][y] = Grid::BUSH;
			GridManager::grid[i][y + 1] = Grid::BUSH;
		}
	}
}
