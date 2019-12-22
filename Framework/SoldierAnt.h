#pragma once
#include "GameObject.h"
#include "CircleCollider.h"
#include "GridManager.h"

class SoldierAnt :
	public GameObject
{
	float timeCheck;
	float timeCount;
	float motionTimer;

public:
	SoldierAnt(int x, int y);
	~SoldierAnt();

	float moveSpeed;
	bool attackAvail, attackMotion;
	int x, y;
	int destX, destY;
	bool isStop;

	Vector2 curCameraPos;
	
	CircleCollider* col;
	std::vector<Node> moveList;
	GridManager* gridManager;

	Vector2* target;

	virtual void Update();

	void SetDest();
	void ResetDest();

	void AttackAvail();

	void AttackMotion();
};

