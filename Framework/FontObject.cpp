#include "stdafx.h"
#include "FontObject.h"

FontObject::FontObject(const wchar_t* str, Vector2 position, float rotation, Vector2 scale, const wchar_t* fontName, float fontSize, float red, float green, float blue, float alpha, bool isBold) :
	GameObject(fontRenderer = new FontRenderer())
{
	font = new Font(fontName, fontSize, red, green, blue, alpha, isBold);
	fontRenderer->font = this->font;
	fontRenderer->text = (wchar_t*)str;

	transform->SetPosition(position);
	transform->SetRotation(rotation);
	transform->SetScale(scale);
}

FontObject::~FontObject()
{
	SAFE_DELETE(font);
	SAFE_DELETE(fontRenderer);
}

void FontObject::SetText(const wchar_t* str)
{
	fontRenderer->text = (wchar_t*)str;
}