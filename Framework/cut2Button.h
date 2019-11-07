#pragma once
#include "InputManager.h"
#include "Button.h"
class cut2Button :
	public Button
{
public:
	cut2Button(float x, float y);
	~cut2Button();

	virtual void OnClick();
};

