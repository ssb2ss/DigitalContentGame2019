#pragma once
#include "GameObject.h"
class Water :
	public GameObject
{
public:
	int x, y;
	bool isDestroy;

	Water(int x, int y);
	~Water();

	virtual void Update();
};

