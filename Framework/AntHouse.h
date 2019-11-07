#pragma once
#include "GameObject.h"
#include "Ant.h"
#include "AntManager.h"
#include "TimeManager.h"
class AntHouse :
	public GameObject
{
	AntManager* am;
	int level;
	float timeSave;
public:
	AntHouse(int x, int y, AntManager* antManager);
	~AntHouse();

	int x, y;

	void SetLevel(int l);
	int GetLevel();

	void GenerateAnt();
	virtual void Update();
private:


	void SetGrid();
};