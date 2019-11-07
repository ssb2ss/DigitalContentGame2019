#pragma once
#include "GameObject.h"
#include "Build.h"
#include "Bush.h"
#include "Food.h"
#include "FootPrint.h"
#include "Stone.h"
#include "Trash.h"
#include "Water.h"

#include "DayManager.h"

class ObjectManager :
	public GameObject
{
	int dayCheck;
	int frameCount;
public:
	ObjectManager();
	~ObjectManager();

	//새 오브젝트 추가시 ABC 순으로 추가 바람

	std::list<Build*> buildList;
	std::list<Bush*> bushList;
	std::list<Food*> foodList;
	std::list<FootPrint*> footPrintList;
	std::list<Stone*> stoneList;
	std::list<Trash*> trashList;
	std::list<Water*> waterList;

	Build* PushBackObject(Build* b);
	Bush* PushBackObject(Bush* b);
	Food* PushBackObject(Food* f);
	FootPrint* PushBackObject(FootPrint* f);
	Stone* PushBackObject(Stone* s);
	Trash* PushBackObject(Trash* t);
	Water* PushBackObject(Water* w);

	void Destroy(Build* b);
	void Destroy(Bush* b);
	void Destroy(Food* f);
	void Destroy(FootPrint* f);
	void Destroy(Stone* s);
	void Destroy(Trash* t);
	void Destroy(Water* w);

	virtual void Update();
	virtual void LateUpdate();

private:
	std::list<Build*> buildDestroyed;
	std::list<Bush*> bushDestroyed;
	std::list<Food*> foodDestroyed;
	std::list<FootPrint*> footPrintDestroyed;
	std::list<Stone*> stoneDestroyed;
	std::list<Trash*> trashDestroyed;
	std::list<Water*> waterDestroyed;

	void Remove();


	
};

