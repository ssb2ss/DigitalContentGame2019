#pragma once
#include "GameObject.h"
#include "AABBCollider.h"
class PlusButton :
	public GameObject
{
	int state;
	float goalScale;
public:
	AABBCollider* col;

	PlusButton(float x, float y, int state);
	~PlusButton();

	virtual void Update();
};