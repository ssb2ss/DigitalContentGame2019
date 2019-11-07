#pragma once
#include "Component.h"
#include "ResourceManager.h"
#include "Transform.h"

//�������� ���õ� ���� �� ��ü
class Renderer :
	public Component
{
public:
	Renderer();
	Renderer(Sprite* startSprite, float alpha = 1.0f);
protected:
	Sprite* currentSprite;	//���� ǥ���� ��������Ʈ�� ����
	float alpha;
	bool initialized;		//��������Ʈ�� �ִ���
	int width, height;
	int layer;				//0:���, 1:����, 2:�⺻, 3:UI ,4:���̵�ƿ� ����ȭ��

public:
	bool GetInitialized();
	Sprite& GetSprite();
	int GetWidth();
	int GetHeight();
	float GetAlpha();
	void SetAlpha(float a);
	int GetLayer();
	void SetLayer(int l);
	virtual void Update() {}
	virtual void Render(ID2D1HwndRenderTarget& renderTarget, Transform& transform);
};

