#pragma once
#include "GameObject.h"
class CutImage :
	public GameObject
{
	int index;
public:
	CutImage();
	~CutImage();

	virtual void Update();
};

