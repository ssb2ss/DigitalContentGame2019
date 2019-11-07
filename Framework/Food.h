#pragma once
#include "GameObject.h"
class Food :
	public GameObject
{
public:
	int x, y, state;

	Food(int x, int y, int state);
	~Food();

	void SetGrid();
	void ChangeSprite(const wchar_t* path);
};