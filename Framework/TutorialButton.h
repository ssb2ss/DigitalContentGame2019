#pragma once
#include "Button.h"
class TutorialButton :
	public Button
{

public:
	TutorialButton(float x, float y);
	~TutorialButton();


	virtual void OnClick();
};

