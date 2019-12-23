#pragma once
#include "GameObject.h"
#include "AntManager.h"
#include "EnemyManager.h"
#include "AntHouse.h"
#include "ObjectManager.h"
#include "CharacterStatusUI.h"
#include "SelectedStatusUI.h"
#include "SelectedButton.h"
#include "PlusButton.h"
#include "NoAntUI.h"
#include "DayManager.h"
#include "FightManager.h"
#include "Ping.h"
#include "FontObject.h"

class GameManager :
	public GameObject
{
	static GameManager* instance;

	int oldX, oldY, curX, curY;
	int currentDay;
	int antDieCheck;

	float cameraSpeed;

	int mapCheck;


public:

	Vector2 cameraPos;

	GameObject* mapBackground;
	GameObject* gridBG;

	AntManager* antManager;
	EnemyManager* enemyManager;

	FightManager* fightManager;

	AntHouse* antHouse;

	Ping* ping;
	GameObject* drag;
	float dragX, dragY;

	ObjectManager* objectManager;
	DayManager* dayManager;

	CharacterStatusUI* charStatus;
	SelectedStatusUI* selectedStatus;
	SelectedButton* selectedButton;

	wchar_t antNumber[4];
	FontObject* antNumberText;

	wchar_t dayNumber[4];
	FontObject* dayNumberText;

	PlusButton* houseupButton;
	PlusButton* houseaddButton;
	PlusButton* antaddButton;

	NoAntUI* noAnt;

	AntHouse* tempHouse;
public:
	static GameManager* GetInstance();

	GameManager();
	~GameManager();

	virtual void Update();

	Vector2 GetGridPos(int x, int y);
	int GetPosGridX(Vector2 pos);
	int GetPosGridX(float _x);
	int GetPosGridY(Vector2 pos);
	int GetPosGridY(float _y);

private:
	void SetObstacle(int map);

	void CheckMouseAction();
	void ManageAnt();
	void ChangeDay();
	void ManageDay();

	void ManageCamera();

	void SetPing(int x, int y);
	void SetSelectedUI(StatusUI state, int x, int y);

	void OnClickSelectedButton();

	void OnHouseUp();
	void OnHouseAdd();
	void OnAntAdd();

	void OnMapChange();

	void SpriteChange(GameObject* g, const wchar_t* path);

};

