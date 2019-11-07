#pragma once
#include "InputManager.h"
#include "Button.h"
class cut1Button :
	public Button
{
public:
	cut1Button(float x, float y);
	~cut1Button();

	virtual void OnClick();
	

	
};

