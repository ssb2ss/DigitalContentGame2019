#pragma once
#include "GameObject.h"
#include "Ant.h"
#include "SoldierAnt.h"

class AntManager :
	public GameObject
{
public:
	AntManager();
	~AntManager();

	std::list<Ant*> antList;
	std::list<Ant*> currentAntGroup;
	std::list<SoldierAnt*> soldierList;

	Ant* PushBackAnt(Ant* a);
	SoldierAnt* PushBackAnt(SoldierAnt* a);
	void Destroy(Ant* a);
	void Destroy(SoldierAnt* a);
	virtual void Update();
	virtual void LateUpdate();

private:
	std::list<Ant*> destroyedAnt;
	std::list<SoldierAnt*> destroyedSoldier;
	void Remove();
};

