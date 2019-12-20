#pragma once
#include "Renderer.h"
#include "Font.h"

//Renderer�� ��ӹ޴� FontRendrer�Լ��Դϴ�.
class FontRenderer :
	public Renderer
{
public:
	FontRenderer(wchar_t text[] = nullptr, Font* font = nullptr);
	Font* font;
	wchar_t* text;
	virtual void Render(ID2D1HwndRenderTarget& renderTarget, Transform& transform);
};

