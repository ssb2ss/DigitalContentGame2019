#pragma once
#include "GameObject.h"
#include "Build.h"
#include "Bush.h"
#include "Food.h"
#include "FootPrint.h"
#include "Stone.h"
#include "Trash.h"
#include "Water.h"

#include "AntHouse.h"

class ObjectManager :
	public GameObject
{
	int dayCheck;
	int frameCount;
	float timeCount;

	bool isGenerate;
	int main, sub[3];
public:
	ObjectManager();
	~ObjectManager();

	//�� ������Ʈ �߰��� ABC ������ �߰� �ٶ�

	std::list<Build*> buildList;
	std::list<Bush*> bushList;
	std::list<Food*> foodList;
	std::list<FootPrint*> footPrintList;
	std::list<Stone*> stoneList;
	std::list<Trash*> trashList;
	std::list<Water*> waterList;

	std::list<AntHouse*> antHouseList;

	Build* PushBackObject(Build* b);
	Bush* PushBackObject(Bush* b);
	Food* PushBackObject(Food* f);
	FootPrint* PushBackObject(FootPrint* f);
	Stone* PushBackObject(Stone* s);
	Trash* PushBackObject(Trash* t);
	Water* PushBackObject(Water* w);

	AntHouse* PushBackObject(AntHouse* a);

	void Destroy(Build* b);
	void Destroy(Bush* b);
	void Destroy(Food* f);
	void Destroy(FootPrint* f);
	void Destroy(Stone* s);
	void Destroy(Trash* t);
	void Destroy(Water* w);

	void Destroy(AntHouse* a);

	virtual void Update();
	virtual void LateUpdate();

	void GenerateObjects(int day, int sub1, int sub2, int sub3);

private:
	std::list<Build*> buildDestroyed;
	std::list<Bush*> bushDestroyed;
	std::list<Food*> foodDestroyed;
	std::list<FootPrint*> footPrintDestroyed;
	std::list<Stone*> stoneDestroyed;
	std::list<Trash*> trashDestroyed;
	std::list<Water*> waterDestroyed;

	std::list<AntHouse*> antHouseDestroyed;

	void Remove();

	void GenerateObstacle(int state);

	void GenerateBuild(int state);
	void GenerateFood(int state);
	void GenerateTrash(int state);
	void GenerateWater();
	
};

