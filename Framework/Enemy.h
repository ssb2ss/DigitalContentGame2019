#pragma once
#include "GameObject.h"
#include "CircleCollider.h"
#include "AntManager.h"

class Enemy :
	public GameObject
{
	bool isStop;
	bool moveCheck;
	float attackCheck;

	float timeCheck;
	float timeCount;
	float motionTimer;

	float moveSpeed;

	AntManager *am;
	float saveTime;

public:
	Enemy(int x, int y);
	~Enemy();

	int x,  y;
	int destX, destY;
	bool isEnd;

	int curState; //0  idle   1  randomMove   
	int hp;
	CircleCollider * col;
	GridManager *grid;


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

