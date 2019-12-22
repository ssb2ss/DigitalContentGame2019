#pragma once
#include "GameObject.h"
#include "CircleCollider.h"
#include "GridManager.h"

class SoldierAnt :
	public GameObject
{
public:
	SoldierAnt(int x, int y);
	~SoldierAnt();

	float moveSpeed;
	int x, y;
	
	CircleCollider* col;
	std::vector<Node> moveList;
	GridManager* gridManager;
};

