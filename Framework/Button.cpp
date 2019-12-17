#include "stdafx.h"
#include "Button.h"
#include "InputManager.h"


Button::Button(const wchar_t* imagePath, float x, float y) :
	GameObject(imagePath, Vector2(x, y))
{
	col = new AABBCollider(*transform, Vector2(renderer->GetWidth(), renderer->GetHeight()));
}

Button::~Button()
{
	SAFE_DELETE(col);
}

void Button::Update()
{
	if (col->Intersected(InputManager::GetMouseVector2()) && InputManager::GetKeyDown(VK_LBUTTON))
		OnClick();
}