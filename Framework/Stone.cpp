#include "stdafx.h"
#include "Stone.h"
#include "GridManager.h"
#include "GameManager.h"
#include "Scene.h"

Stone::Stone(int x, int y, int state) :
	GameObject(L"resources/sprites/stone_1.png", GameManager::GetInstance()->GetGridPos(x, y)), x(x), y(y), state(state)
{

	if (state == ObstacleEnum::STONE_1)
	{
		ChangeSprite(L"resources/sprites/stone_1.png");
		transform->SetScale(1.8f, 1.8f);
	}
	else if (state == ObstacleEnum::STONE_2)
	{
		ChangeSprite(L"resources/sprites/stone_2.png");
		transform->SetScale(1.5f, 1.5f);
	}
	else if (state == ObstacleEnum::STONE_3)
	{
		ChangeSprite(L"resources/sprites/stone_3.png");
		transform->SetScale(1.3f, 1.3f);
	}
	else if (state == ObstacleEnum::BRICK)
	{
		ChangeSprite(L"resources/sprites/brick.png");
		transform->SetScale(2.2f, 2.2f);
	}
	else if (state == ObstacleEnum::PERSONA)
	{
		ChangeSprite(L"resources/sprites/persona.png");
		transform->SetRotation(90);
		transform->SetScale(1.f, 1.f);
	}
	else if (state == ObstacleEnum::AIRPOT)
	{
		ChangeSprite(L"resources/sprites/airpot.png");
		transform->SetScale(2.f, 2.f);
	}
	else if (state == ObstacleEnum::ERODE)
	{
		ChangeSprite(L"resources/sprites/erode.png");
		transform->SetScale(1.2f, 1.2f);
	}

	SetGrid();
}

Stone::~Stone()
{
	if (state == ObstacleEnum::AIRPOT)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::EMPTY;
			}
		}
	}
	else
	{
		for (int i = x - 7; i <= x + 7; i++)
		{
			for (int j = y - 5; j <= y + 5; j++)
			{
				GridManager::grid[i][j] = Grid::EMPTY;
			}
		}
	}
}

void Stone::SetGrid()
{
	if (state == ObstacleEnum::AIRPOT)
	{
		for (int i = x - 3; i <= x + 3; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				GridManager::grid[i][j] = Grid::OBSTACLE;
			}
		}
	}
	else
	{
		for (int i = x - 7; i <= x + 7; i++)
		{
			for (int j = y - 5; j <= y + 5; j++)
			{
				GridManager::grid[i][j] = Grid::OBSTACLE;
			}
		}
	}
}

void Stone::ChangeSprite(const wchar_t * path)
{
	SAFE_DELETE(renderer);
	renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(path, 0, 0));
}
