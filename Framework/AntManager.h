#pragma once
#include "GameObject.h"
#include "Ant.h"
class AntManager :
	public GameObject
{
public:
	AntManager();
	~AntManager();

	std::list<Ant*> antList;

	Ant* PushBackAnt(Ant* a);
	void Destroy(Ant* a);
	virtual void Update();
	virtual void LateUpdate();

private:
	std::list<Ant*> destroyed;
	void Remove();
};

