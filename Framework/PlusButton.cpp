#include "stdafx.h"
#include "PlusButton.h"
#include "Scene.h"

PlusButton::PlusButton(float x, float y, int state) :
	GameObject(L"resources/sprites/UI/houseup_button.png", Vector2(x, y)), state(state)
{
	if (state == 0)
	{
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/UI/houseup_button.png", 0, 0));
	}
	else if (state == 1)
	{
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/UI/shieldadd_button.png", 0, 0));
	}
	renderer->SetLayer(3);

	col = new AABBCollider(*transform, 180, 180);
}

PlusButton::~PlusButton()
{
	SAFE_DELETE(col);
}
