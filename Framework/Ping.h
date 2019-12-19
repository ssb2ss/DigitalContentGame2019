#pragma once
#include "GameObject.h"
class Ping :
	public GameObject
{
public:
	Ping();
	~Ping();

	int x, y;

	virtual void Update();
};

