#pragma once
#include "stdafx.h"
#include "Renderer.h"

//���ӿ�����Ʈ ��ü�Դϴ�.
//���ӿ��� ǥ���� ��� ��ü�� �ݵ�� GameObject�� ��ӹ��� ��ü�� �����Ǿ�� �մϴ�.
//���ӿ��� ǥ���� ��� ��ü�� �ݵ�� Scene�� PushBack�Ǿ�� ���������� �����˴ϴ�.

class GameObject
{
public:
	//GameObject() ó�� ȣ���� �� �ִ� �������Դϴ�. �̹��� �ε尡 �ʿ������� ����մϴ�.
	GameObject(Vector2 position = Vector2(), float angle = 0.0f, Vector2 scale = Vector2(1.0f, 1.0f));

	//GameObject(L"image.png"); ó�� ȣ���� �� �ִ� �������Դϴ�. �ϳ��� �̹����� �ε��� ��� ����մϴ�.
	//TestObject.h, TestObject.cpp�� �����ϼ���.
	GameObject(const wchar_t* imagePath, Vector2 position = Vector2(), float angle = 0.0f, Vector2 scale = Vector2(1.0f, 1.0f));

	//GameObject(new AnimationRenderer()); ó�� ȣ���� �� �ִ� �������Դϴ�. �ִϸ��̼��� �̿��� ��� ����մϴ�.
	//Player.h, Player.cpp�� �����ϼ���.
	GameObject(Renderer* renderer, Vector2 position = Vector2(), float angle = 0.0f, Vector2 scale = Vector2(1.0f, 1.0f));
	virtual ~GameObject();
private:
	bool isActive;
public:
	std::string name;		//��ü ������ �̸���
	Transform* transform;	//��ġ, ȸ����, ũ�Ⱚ ���� ����
	Renderer* renderer;		//Render�� ������ ��ü�Դϴ�. �Ƹ� ���� �ǵ�� ���� ���� ���� ���Դϴ�.

public:
	virtual void Start() {}				//������Ʈ�� ó�� ������� �� ȣ��
	virtual void Update() {}			//�� �����Ӹ��� ȣ��
	virtual void LateUpdate() {}		//Update�� ȣ��� ���� ȣ��
	virtual void OnDestroy() {}			//������Ʈ�� ������ �� ȣ��

public:
	bool GetActive();
	void SetActive(bool mode);
};

