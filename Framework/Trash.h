#pragma once
#include "GameObject.h"

enum TrashEnum
{
	TISSUE,
	BOTTLE,
	CAN,
	MASK,
	LUNCH,
};

class Trash :
	public GameObject
{
public:
	int x, y, state;

	Trash(int x, int y, int state);
	~Trash();

	void SetGrid();
	void ChangeSprite(const wchar_t* path);
};

