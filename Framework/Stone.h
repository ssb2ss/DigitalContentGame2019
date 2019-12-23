#pragma once
#include "GameObject.h"

enum ObstacleEnum
{
	STONE_1,
	STONE_2,
	STONE_3,
	BRICK,
	PERSONA,
	AIRPOD,
	ERODE,
	LIGHT,
	CONS_ROCK,
	DUST,
	POSTER,
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

