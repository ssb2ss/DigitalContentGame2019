#pragma once
#include "GameObject.h"
#include "CircleCollider.h"

class Enemy :
	public GameObject
{
	
	float timeCheck;
	float timeCount;
public:
	Enemy(int x, int y);
	~Enemy();

	int x, y;

	int hp;
	CircleCollider * col;

	void Damage();

	void AttackAvail();
	bool attackAvail;
};

