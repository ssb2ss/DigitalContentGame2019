#pragma once
#include "GameObject.h"
#include "AABBCollider.h"
class Button :
	public GameObject
{
public:
	Button(const wchar_t* imagePath, float x, float y);
	~Button();

	AABBCollider* col;

	virtual void Update();
	virtual void OnClick() = 0;
};