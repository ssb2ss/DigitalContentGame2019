#pragma once
#include "Scene.h"
class TutorialScene :
	public Scene
{
public:

	virtual void Initialize();

	GameObject* cut1;
	GameObject* cut2;
	GameObject* cut3;


};

