#pragma once
#include "Button.h"
class ExitButton :
	public Button
{
public:
	ExitButton(float x, float y);
	~ExitButton();

	virtual void OnClick();
};

