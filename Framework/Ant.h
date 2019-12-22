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
	ANT_BUILD_3,
	ANT_FOOD_1,
	ANT_FOOD_2,
	ANT_FOOD_3,
	ANT_FOOD_4,
	ANT_FOOD_5,
	ANT_FOOD_6,
	ANT_FOOD_7,
	ANT_FOOD_8,
	ANT_FOOD_9,
	ANT_FOOD_10,
	ANT_TRASH_1,
	ANT_TRASH_2,
	ANT_TRASH_3,
	ANT_TRASH_4,
	ANT_TRASH_5,
};

class Ant :
	public GameObject
{
	float timeCheck;
	float timeCount;
	
public:
	Ant(int x, int y);
	~Ant();

	float moveSpeed;
	bool attackAvail;
	int x, y;
	int destX, destY;
	bool isStop, isSelected;
	bool isCarrying;
	StatusUI state;

	Vector2 curCameraPos;

	CircleCollider* col;
	std::vector<Node> moveList;
	GridManager* gridManager;

	virtual void Update();

	void ChangeSprite(AntSprite a);

	void Move();
	void SetDest();
	void ResetDest();

	void SetCarry(StatusUI _state);

	void AntAttack();

	void AttackAvail();
};

