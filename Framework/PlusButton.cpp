#include "stdafx.h"
#include "PlusButton.h"
#include "Scene.h"
#include "GameManager.h"
#include "InputManager.h"

PlusButton::PlusButton(float x, float y, int state) :
	GameObject(L"resources/sprites/UI/houseup_button.png", Vector2(x, y)), state(state), goalScale(1)
{
	if (state == 0)
	{
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/UI/houseup_button.png", 0, 0));
	}
	else if (state == 1)
	{
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/UI/houseadd_button.png", 0, 0));
	}
	else if (state == 2)
	{
		SAFE_DELETE(renderer);
		renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/UI/antadd_button.png", 0, 0));
	}
	renderer->SetLayer(3);

	col = new AABBCollider(*transform, 180, 180);
}

PlusButton::~PlusButton()
{
	SAFE_DELETE(col);
}

void PlusButton::Update()
{
	if (state == 0)
	{
		if (GameManager::GetInstance()->charStatus->woodValue < GameManager::GetInstance()->antHouse->GetLevel() + 2)
		{
			renderer->SetAlpha(0.5f);
		}
		else
		{
			renderer->SetAlpha(1);
		}
	}
	else if (state == 1)
	{
		if (GameManager::GetInstance()->charStatus->woodValue < 4)
		{
			renderer->SetAlpha(0.5f);
		}
		else
		{
			renderer->SetAlpha(1);
		}
	}
	else if (state == 2)
	{
		if (GameManager::GetInstance()->charStatus->woodValue < 1)
		{
			renderer->SetAlpha(0.5f);
		}
		else
		{
			renderer->SetAlpha(1);
		}
	}

	if (col->Intersected(InputManager::GetMouseVector2()))
		if (InputManager::GetKeyPressed(VK_LBUTTON))
			goalScale = 1.f;
		else
			goalScale = 1.1f;
	else
		goalScale = 1.f;

	transform->scale += Vector2((goalScale - transform->scale.x) / 6.f, (goalScale - transform->scale.y) / 6.f);
}
