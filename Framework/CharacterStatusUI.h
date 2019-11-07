#pragma once
#include "GameObject.h"
class CharacterStatusUI :
	public GameObject
{
public:
	CharacterStatusUI();
	~CharacterStatusUI();

	int waterValue, foodValue, woodValue;

	GameObject* waterStatus;
	GameObject* foodStatus;
	GameObject* waterPoint[10];
	GameObject* foodPoint[10];
	GameObject* woodPoint[10];

	void Notify();
};

