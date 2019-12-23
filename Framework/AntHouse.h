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
	AntHouse(int x, int y);
	~AntHouse();

	bool isSet;
	int x, y;
	int generateAntCount;

	void SetLevel(int l);
	int GetLevel();

	void GenerateAnt();
	virtual void Update();

	void Setting();
private:


	void SetGrid();
};