#include "stdafx.h"
#include "AntHouse.h"
#include "GridManager.h"
#include "Scene.h"
#include "GameManager.h"
#include "InputManager.h"

AntHouse::AntHouse(int x, int y) :
	GameObject(L"resources/sprites/house_1.png", GameManager::GetInstance()->GetGridPos(x, y)), x(x), y(y), level(1), am(GameManager::GetInstance()->antManager), timeSave(0), generateAntCount(1), isSet(false)
{
	transform->SetScale(0.8f, 0.8f);
	renderer->SetLayer(0);

	SetGrid();
}

AntHouse::~AntHouse()
{
	if (level == 1)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			if ((i >= x - 3 && i <= x - 2) || (i >= x + 2 && i <= x + 3))
			{
				GridManager::grid[i][y + 1] = Grid::EMPTY;
			}
			else
			{
				for (int j = y - 2; j <= y + 1; j++)
				{
					GridManager::grid[i][j] = Grid::EMPTY;
				}
			}
		}
	}
	else if (level == 2)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			if (i == x - 3 || i == x + 3)
			{
				GridManager::grid[i][y + 1] = Grid::EMPTY;
			}
			else if (i == x - 2 || i == x + 2)
			{
				GridManager::grid[i][y] = Grid::EMPTY;
				GridManager::grid[i][y + 1] = Grid::EMPTY;
			}
			else
			{
				for (int j = y - 2; j <= y + 1; j++)
				{
					GridManager::grid[i][j] = Grid::EMPTY;
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
				GridManager::grid[i][y + 1] = Grid::EMPTY;
			}
			else if (i >= x + 1 && i <= x + 2)
			{
				GridManager::grid[i][y] = Grid::EMPTY;
				GridManager::grid[i][y + 1] = Grid::EMPTY;
			}
			else if (i == x - 2)
			{
				for (int j = y - 1; j <= y + 1; j++)
				{
					GridManager::grid[i][j] = Grid::EMPTY;
				}
			}
			else
			{
				for (int j = y - 2; j <= y + 1; j++)
				{
					GridManager::grid[i][j] = Grid::EMPTY;
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
				GridManager::grid[i][y + 2] = Grid::EMPTY;
			}
			else if (i == x - 4 || i == x + 4)
			{
				GridManager::grid[i][y + 1] = Grid::EMPTY;
				GridManager::grid[i][y + 2] = Grid::EMPTY;
			}
			else if ((i >= x - 3 && i <= x - 2) || (i >= x + 2 && i <= x + 3))
			{
				for (int j = y; j <= y + 2; j++)
				{
					GridManager::grid[i][j] = Grid::EMPTY;
				}
			}
			else if (i == x - 1)
			{
				for (int j = y - 1; j <= y + 2; j++)
				{
					GridManager::grid[i][j] = Grid::EMPTY;
				}
			}
			else
			{
				for (int j = y - 2; j <= y + 2; j++)
				{
					GridManager::grid[i][j] = Grid::EMPTY;
				}
			}
		}
	}
}

void AntHouse::SetLevel(int l)
{
	level = l;
	if (level == 1)
	{
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/house_1.png", 0, 0));
		renderer->SetLayer(0);
		generateAntCount = 1;
	}
	else if (level == 2)
	{
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/house_2.png", 0, 0));
		renderer->SetLayer(0);
		generateAntCount = 2;
	}
	else if (level == 3)
	{
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/house_3.png", 0, 0));
		renderer->SetLayer(0);
		generateAntCount = 3;
	}
	else if (level == 4)
	{
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/house_4.png", 0, 0));
		renderer->SetLayer(0);
		generateAntCount = 4;
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
	if (timeSave >= 12)
	{
		for (int i = 0; i < generateAntCount; i++)
		{
			if (am->antList.size() <= 40)
			{
				am->PushBackAnt(new Ant(x, y + 2));
			}
		}


		timeSave = 0;
	}
}

void AntHouse::Update()
{
	if (!isSet)
	{
		int mx = InputManager::GetMouseX();
		int my = InputManager::GetMouseY();

		if (mx - 40 >= 0 && mx - 40 <= 1464 && my - 40 >= 0 && my - 40 <= 824)
		{

			int gx = GameManager::GetInstance()->GetPosGridX(mx);
			int gy = GameManager::GetInstance()->GetPosGridY(my);

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

				for (int i = x - 3; i <= x + 3; i++)
				{
					if ((i >= x - 3 && i <= x - 2) || (i >= x + 2 && i <= x + 3))
					{
						if (GridManager::grid[i][y + 1] != Grid::EMPTY)
						{
							temp = false;
						}
					}
					else
					{
						for (int j = y - 2; j <= y + 1; j++)
						{
							if (GridManager::grid[i][j] != Grid::EMPTY)
							{
								temp = false;
							}
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

			transform->SetPosition(GameManager::GetInstance()->GetGridPos(x, y));

		}
		else
		{
			renderer->SetAlpha(0.f);
		}

	}
	else
	{
		GenerateAnt();
	}
}

void AntHouse::Setting()
{
	isSet = true;
	renderer->SetAlpha(1.f);

	transform->SetPosition(GameManager::GetInstance()->GetGridPos(x, y));

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
