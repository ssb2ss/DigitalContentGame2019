#include "stdafx.h"
#include "SelectedButton.h"
#include "Scene.h"
#include "InputManager.h"


SelectedButton::SelectedButton(float x, float y) :
	GameObject(L"resources/sprites/UI/move_button.png", Vector2(x, y)), goalScale(1)
{
	renderer->SetLayer(3);

	col = new AABBCollider(*transform, Vector2(renderer->GetWidth(), renderer->GetHeight()));

	SetState(StatusUI::ANTHOUSE, 0, 0);
}

SelectedButton::~SelectedButton()
{
	SAFE_DELETE(col);
}

void SelectedButton::Update()
{
	if (col->Intersected(InputManager::GetMouseVector2()))
		if (InputManager::GetKeyPressed(VK_LBUTTON))
			goalScale = 1.f;
		else
			goalScale = 1.1f;
	else
		goalScale = 1.f;

	transform->scale += Vector2((goalScale - transform->scale.x) / 6.f, (goalScale - transform->scale.y) / 6.f);
}

void SelectedButton::SetState(StatusUI s, int _x, int _y)
{
	state = s;
	x = _x;
	y = _y;

	if (state == StatusUI::UI_WATER)
	{
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/UI/drink_button.png", 0, 0));
		renderer->SetLayer(3);
	}
	else
	{
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/UI/move_button.png", 0, 0));
		renderer->SetLayer(3);
	}

	if (state == StatusUI::ANTHOUSE || state == StatusUI::UI_BUSH)
		SetActive(false);
	else
		SetActive(true);
}
