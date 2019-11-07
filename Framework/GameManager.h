#pragma once
#include "GameObject.h"
#include "AntManager.h"
#include "AntHouse.h"
#include "ObjectManager.h"
#include "CharacterStatusUI.h"
#include "SelectedStatusUI.h"
#include "SelectedButton.h"
#include "PlusButton.h"
#include "NoAntUI.h"
#include "DayManager.h"

class GameManager :
	public GameObject
{
	int oldX, oldY, curX, curY;
	int currentDay;
	int antDieCheck;

	AntManager* antManager;
	std::list<Ant*> currentAntGroup;

	AntHouse* antHouse;

	GameObject* ping;
	GameObject* drag;
	float dragX, dragY;

	ObjectManager* objectManager;
	DayManager* dayManager;

	CharacterStatusUI* charStatus;
	SelectedStatusUI* selectedStatus;
	SelectedButton* selectedButton;

	PlusButton* houseupButton;
	PlusButton* sheildaddButton;

	NoAntUI* noAnt;

	Bush* tempBush;
public:
	GameManager();
	~GameManager();

	virtual void Update();

private:
	void SetWaterObstacle();

	void CheckMouseAction();

	void SetPing(int x, int y);
	void SetSelectedUI(StatusUI state, int x, int y);

	void OnClickSelectedButton();

	void OnHouseUp();
	void OnShieldAdd();
};

