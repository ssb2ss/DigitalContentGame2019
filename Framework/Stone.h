#pragma once
#include "GameObject.h"

enum ObstacleEnum
{
	STONE_1,
	STONE_2,
	STONE_3,
	BRICK,
	PERSONA,
	AIRPOT,
	ERODE,
};

class Stone :
	public GameObject
{
public:
	int x, y, state;

	Stone(int x, int y, int state);
	~Stone();

	void SetGrid();
	void ChangeSprite(const wchar_t* path);
};

