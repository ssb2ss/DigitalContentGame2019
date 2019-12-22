#include "stdafx.h"
#include "Stone.h"
#include "GridManager.h"
#include "GameManager.h"
#include "Scene.h"

Stone::Stone(int x, int y, int state) :
	GameObject(L"resources/sprites/stone_1.png", GameManager::GetInstance()->GetGridPos(x, y)), x(x), y(y), state(state)
{
	transform->SetScale(0.8f, 0.8f);

	if (state == ObstacleEnum::STONE_1)
		ChangeSprite(L"resources/sprites/stone_1.png");
	else if (state == ObstacleEnum::STONE_2)
		ChangeSprite(L"resources/sprites/stone_2.png");
	else if (state == ObstacleEnum::STONE_3)
		ChangeSprite(L"resources/sprites/stone_3.png");
	else if (state == ObstacleEnum::BRICK)
		ChangeSprite(L"resources/sprites/brick.png");
	else if (state == ObstacleEnum::PERSONA)
		ChangeSprite(L"resources/sprites/persona.png");
	else if (state == ObstacleEnum::AIRPOT)
		ChangeSprite(L"resources/sprites/airpot.png");
	else if (state == ObstacleEnum::ERODE)
		ChangeSprite(L"resources/sprites/erode.png");

	SetGrid();
}

Stone::~Stone()
{
	for (int i = x - 3; i <= x + 3; i++)
	{
		for (int j = y - 2; j <= y + 2; j++)
		{
			GridManager::grid[i][j] = Grid::EMPTY;
		}
	}
}

void Stone::SetGrid()
{
	for (int i = x - 3; i <= x + 3; i++)
	{
		for (int j = y - 2; j <= y + 2; j++)
		{
			GridManager::grid[i][j] = Grid::OBSTACLE;
		}
	}
}

void Stone::ChangeSprite(const wchar_t * path)
{
	SAFE_DELETE(renderer);
	renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(path, 0, 0));
}
