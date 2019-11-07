#pragma once
#include "Component.h"
#include "ResourceManager.h"
#include "Transform.h"

//렌더링과 관련된 일을 할 객체
class Renderer :
	public Component
{
public:
	Renderer();
	Renderer(Sprite* startSprite, float alpha = 1.0f);
protected:
	Sprite* currentSprite;	//현재 표시할 스프라이트를 저장
	float alpha;
	bool initialized;		//스프라이트가 있는지
	int width, height;
	int layer;				//0:배경, 1:개미, 2:기본, 3:UI ,4:페이드아웃 검은화면

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

