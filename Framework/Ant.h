#pragma once
#include "GameObject.h"
#include "CircleCollider.h"
#include "GridManager.h"
#include "SelectedStatusUI.h"

enum AntSprite
{
	ANT_IDLE = 0,
	ANT_SELECTED,
	ANT_BUILD_1,
	ANT_BUILD_2,
	ANT_FOOD_1,
	ANT_FOOD_2,
	ANT_FOOD_3,
	ANT_FOOD_4,
	ANT_TRASH_1,
	ANT_TRASH_2,
	ANT_TRASH_3,
};

class Ant :
	public GameObject
{
public:
	Ant(int x, int y);
	~Ant();

	float moveSpeed;
	int x, y;
	int destX, destY;
	bool isStop, isSelected;
	bool isCarrying;
	StatusUI state;

	CircleCollider* col;
	std::vector<Node> moveList;
	GridManager* gridManager;

	virtual void Update();

	void ChangeSprite(AntSprite a);

	void Move();
	void SetDest();
	void ResetDest();

	void SetCarry(StatusUI _state);
};

