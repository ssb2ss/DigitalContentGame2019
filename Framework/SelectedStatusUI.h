#pragma once
#include "GameObject.h"

enum StatusUI
{
	ANTHOUSE = 0,	//������
	UI_BUILD_1,		//������
	UI_BUILD_2,		//��������
	UI_BUSH,		//Ǯ����
	UI_FOOD_1,		//�Ļ�����
	UI_FOOD_2,		//���̽�ũ��
	UI_FOOD_3,		//���� �ν�����
	UI_FOOD_4,		//�޶ѱ�
	UI_TRASH_1,		//��������
	UI_TRASH_2,		//������
	UI_TRASH_3,		//����
	UI_WATER		//�����
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
	StatusValue value[12];
	GameObject* valueIcon[3][4];

	SelectedStatusUI();
	~SelectedStatusUI();

	void SetState(StatusUI newState);

private:
	void ChangeSprite(const wchar_t* path);
	void InitializeStatusValue();
};
