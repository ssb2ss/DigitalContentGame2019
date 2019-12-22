#pragma once
#include "GameObject.h"
#include "CircleCollider.h"
#include "GridManager.h"

class Enemy :
	public GameObject
{
	bool isStop;
	bool moveCheck;
	float attackCheck;

	float timeCheck;
	float timeCount;
	float motionTimer;

	float saveTime;

public:
	Enemy(int x, int y);
	~Enemy();

	int x,  y;
	int destX, destY;
	bool isEnd;

	float moveSpeed;

	int curState; //0  idle   1  randomMove   
	int hp;
	CircleCollider * col;
	CircleCollider* moveCol;
	GridManager *grid;

	Vector2 curCameraPos;

	std::vector<Node> moveList;
	void Idle();
	void setDest();
	virtual void Update();

	void Damage();

	void AttackAvail();
	bool attackAvail;

	void AttackMotion();
	bool attackMotion;

	void RandomMove();



};

