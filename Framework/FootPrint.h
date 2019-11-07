#pragma once
#include "GameObject.h"
class FootPrint :
	public GameObject
{
	int x, y;
public:
	FootPrint(int x, int y);
	~FootPrint();
};

