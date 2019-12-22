#include "stdafx.h"
#include "SoldierAnt.h"
#include "GameManager.h"

SoldierAnt::SoldierAnt(int x, int y) :
	GameObject(L"resources/sprites/ant_soldier.png", GameManager::GetInstance()->GetGridPos(x, y)), moveSpeed(200.f),
	x(x), y(y)
{
	transform->SetScale(0.4f, 0.4f);
	col = new CircleCollider(*transform, 2.f);
}

SoldierAnt::~SoldierAnt()
{
	SAFE_DELETE(col);
}
