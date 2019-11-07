#pragma once
#include "GameObject.h"
class Build :
	public GameObject
{
public:
	int x, y, state;

	Build(int x, int y, int state);
	~Build();

	void SetGrid();
	void ChangeSprite(const wchar_t* path);
};

