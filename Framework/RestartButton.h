#pragma once
#include "Button.h"
class RestartButton :
	public Button
{
public:
	RestartButton(float x, float y);
	~RestartButton();

	virtual void OnClick();
};

