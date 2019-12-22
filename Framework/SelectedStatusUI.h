#pragma once
#include "GameObject.h"

enum StatusUI
{
	ANTHOUSE = 0,	//개미집
	UI_BUILD_1,		//나뭇잎
	UI_BUILD_2,		//나뭇가지
	UI_BUILD_3,		//건축자재(나무)
	UI_BUSH,		//풀더미
	UI_FOOD_1,		//식빵조각
	UI_FOOD_2,		//아이스크림
	UI_FOOD_3,		//과자 부스러기
	UI_FOOD_4,		//피자
	UI_FOOD_5,		//닭꼬치
	UI_FOOD_6,		//당근
	UI_FOOD_7,		//팝콘
	UI_FOOD_8,		//물고기
	UI_FOOD_9,		//솜사탕
	UI_FOOD_10,		//메뚜기
	UI_TRASH_1,		//휴지조각
	UI_TRASH_2,		//유리병
	UI_TRASH_3,		//깡통
	UI_TRASH_4,		//마스크
	UI_WATER,		//물방울
};

typedef struct _StatusValue
{
	int ant;
	int water;
	int food;
	int wood;

	_StatusValue() : ant(0), water(0), food(0), wood(0) {}
	_StatusValue(int ant, int water, int food, int wood = 0) :
		ant(ant), water(water), food(food), wood(wood) {}

} StatusValue;

class SelectedStatusUI :
	public GameObject
{
	StatusUI state;

public:
	StatusValue value[20];
	GameObject* valueIcon[3][4];

	SelectedStatusUI();
	~SelectedStatusUI();

	void SetState(StatusUI newState);

private:
	void ChangeSprite(const wchar_t* path);
	void InitializeStatusValue();
};

