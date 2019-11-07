#pragma once
#include "InputManager.h"
#include "Button.h"
class cut3Button :
	public Button
{
public:
	cut3Button(float x, float y);
	~cut3Button();

	virtual void OnClick();
};

