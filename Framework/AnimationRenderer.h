#pragma once
#include "Renderer.h"
#include "Animation.h"

//�������� ��ӹ޴� ANimationRenderer�Դϴ�
//�ִϸ��̼��� ����ϴ� ��ü�� ��쿡 �ִϸ��̼� ������ ��ü�� �����Ͽ� ����մϴ�.

class AnimationRenderer :
	public Renderer
{
public:
	AnimationRenderer();
	virtual ~AnimationRenderer();
public:
	int currentState;					//���� ������� �ִϸ��̼��� state ��
	Animation* currentAnimation;		//���� ������� �ִϸ��̼� ��ü�� ������ �ּ�
	std::vector<Animation*> animations;	//��� �ִϸ��̼��� ����ִ� ����(�迭 ������ �����̳�)
public:
	void Render(ID2D1HwndRenderTarget& renderTarget, Transform& transform);
public:
	void ChangeAnimation(int state);			//�ִϸ��̼��� �����ϰ� ���� ��� ȣ��
	void PushBackAnimation(Animation* anim);	//���ο� �ִϸ��̼��� ����ϰ� ���� ��� ȣ��
	Animation* FindAnimationByState(int state);	//state���� �Է¹޾� �ش� Animation�� ��ȯ�մϴ�, �������� ���� ��� nullptr�� ��ȯ�մϴ�.
};

