#pragma once
#include "Animation.h"

class SheetAnimation
	:public Animation
{
public:
	//pixelWidth,Height: �� �������� ����,����ũ��
	//ex)4*4 sheet�̰�, ��Ʈ�� �̹��� ũ�Ⱑ 1024*1024�� ���, pixelWidth,Heigt�� ����256,256�� �Է�
	SheetAnimation(const int state, float fps, const wchar_t* sheetPath, int pixelWidth, int pixelHeight, int length);

	//row: �ִϸ��̼� ��Ʈ�� ���� �̹��� ���� ex)4x4 sheet�� ��� 4�� �Է�, ex)8*4 sheet�� ��� 8�� �Է�
	SheetAnimation(const int state, float fps, const wchar_t* sheetPath, int row,  int length);	
public:
	Sprite* sheet;
	int width, height;	//�ִϸ��̼��� �ڸ� ����
	int rowCount;

public:
	//�����ӿ�ũ ���������� �۵��ϴ� �Լ��Դϴ�.
	virtual void SetSourceRect(D2D1_RECT_F& outRect);

public:
	virtual Sprite* GetCurrentSprite();
	virtual Vector2 GetAnimationSize();
	virtual Sprite* UpdateAnim();
	std::vector<D2D1_RECT_F> sourceRects;

};