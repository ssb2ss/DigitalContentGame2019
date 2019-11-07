#pragma once
#include "GameObject.h"
class Bush :
	public GameObject
{
public:
	int x, y;
	bool isSet;

	Bush();
	~Bush();

	virtual void Update();

	void Setting();
};

