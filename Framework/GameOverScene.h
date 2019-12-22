#pragma once
#include "Scene.h"
#include "ExitButton.h"
#include "RestartButton.h"
#include "FontObject.h"

class GameOverScene :
	public Scene
{
public:
	virtual void Initialize();


	GameObject* background;
	GameObject* endGameLogo;
	ExitButton* exitButton;


	wchar_t scoreNumber[4];
	FontObject* scoreText;


	//RestartButton* restartButton;

};

