#pragma once
#include "GameObject.h"
#include "Newspaper.h"


class DayManager :
	public GameObject
{
	float timeOut;

	
	int timeCount;

	float timeAdd;

	bool isFade, isAlphaUp;
public:
	static int dayCount;
	DayManager();
	~DayManager();

	Newspaper *news;
	GameObject* clock;

	GameObject* fade;

	virtual void Update();

	void ClockFlick();


	void ChangeSprite(GameObject* g, const wchar_t* path);

};

