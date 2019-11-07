#pragma once
#include "Scene.h"
#include "GameManager.h"
#include "DayManager.h"

class GameScene :
	public Scene
{
public:
	virtual void Initialize();

	GameManager* gameManager;

};