#pragma once
#include "GameObject.h"
#include "SelectedStatusUI.h"
#include "AABBCollider.h"

class SelectedButton :
	public GameObject
{
public:
	StatusUI state;
	int x, y;
	AABBCollider* col;

	SelectedButton(float x, float y);
	~SelectedButton();

	void SetState(StatusUI s, int _x, int _y);
};

