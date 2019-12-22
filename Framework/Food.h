#pragma once
#include "GameObject.h"

enum FoodEnum
{
	BREAD,
	ICECREAM,
	SNACK,
	PIZZA,
	GRASSHOPPER,
};

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