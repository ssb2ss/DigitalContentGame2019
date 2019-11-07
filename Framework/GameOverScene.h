#pragma once
#include "Scene.h"
#include "ExitButton.h"
#include "RestartButton.h"
class GameOverScene :
	public Scene
{
public:
	virtual void Initialize();


	GameObject* background;
	GameObject* endGameLogo;
	ExitButton* exitButton;
	//RestartButton* restartButton;

};

