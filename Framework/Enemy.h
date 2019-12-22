#pragma once
#include "GameObject.h"
#include "CircleCollider.h"

class Enemy :
	public GameObject
{
	
	float timeCheck;
	float timeCount;
	float motionTimer;
public:
	Enemy(int x, int y);
	~Enemy();

	int x, y;

	int hp;
	CircleCollider * col;

	virtual void Update();

	void Damage();

	void AttackAvail();
	bool attackAvail;

	void AttackMotion();
	bool attackMotion;
};

