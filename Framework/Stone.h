#pragma once
#include "GameObject.h"
class Stone :
	public GameObject
{
public:
	int x, y;

	Stone(int x, int y, bool isBlack = true);
	~Stone();
};

