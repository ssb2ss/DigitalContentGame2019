#pragma once
#include "Scene.h"
#include "StartButton.h"
#include "TutorialButton.h"

class TitleScene :
	public Scene
{
public:
	virtual void Initialize();

	GameObject* background;
	GameObject* title;
	StartButton* startButton;
	TutorialButton* tutorialButton;
};