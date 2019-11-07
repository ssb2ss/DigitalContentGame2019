#pragma once
#include "Button.h"
class StartButton :
	public Button
{
public:
	StartButton(float x, float y);

	virtual void OnClick();
};

