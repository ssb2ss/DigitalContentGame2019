#pragma once
#include "GameObject.h"
#include "FontRenderer.h"

class FontObject :
	public GameObject
{
public:
	FontObject(const wchar_t* str, Vector2 position = Vector2(), float rotation = 0.f, Vector2 scale = Vector2(1.f, 1.f), const wchar_t* fontName = L"Arial", float fontSize = 20.f, float red = 0.f, float green = 0.f, float blue = 0.f, float alpha = 1.f, bool isBold = false);
	~FontObject();

	Font* font;
	FontRenderer* fontRenderer;

	float fontSize;
	float red, green, blue, alpha;
	bool isBold;

public:
	void SetText(const wchar_t* str);
};

