#pragma once
#include "ResourceManager.h"

//�ϳ��� �ִϸ��̼��� ������ ��ü�Դϴ�.
//�߻� Ŭ�����Դϴ�.
//���� ���۽ÿ� ListAnimation, SheetAnimation�� ����մϴ�.
//���̷��� �ִϸ��̼��� �������� �ʾ�����, �ش� Ŭ������ ������ �����ϼž� �մϴ�.
class Animation
{
public:
	Animation(const int state, float fps);
public:
	const int state;		//�ִϸ��̼��� state number
	int currentFrame;			//���� frame number
	float frameTime;		//���� �ִϸ��̼��� �ð�
	int length;				//�ִϸ��̼��� ������ ����
protected:
	float fps;				//�ִϸ��̼��� ������ fps
	float reciprocalFPS;	//1/fps

public:
	void SetFPS(float fps);
	float GetFPS(float fps);
public:
	virtual void SetSourceRect(D2D1_RECT_F& outRect)=0;
	virtual Sprite* UpdateAnim() = 0;
	virtual Sprite* GetCurrentSprite() = 0;
	virtual Vector2 GetAnimationSize() = 0;
	virtual void Reset();
};