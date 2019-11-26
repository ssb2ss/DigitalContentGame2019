#include "stdafx.h"
#include "CharacterStatusUI.h"
#include "Scene.h"
#include "GameOverScene.h"

//积己 : 全己格

CharacterStatusUI::CharacterStatusUI()
{
	waterValue = 5;
	foodValue = 5;
	woodValue = 0;

	waterStatus = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/UI/water_status.png", Vector2(180, 50)));
	waterStatus->transform->SetScale(0.8f, 0.8f);
	waterStatus->renderer->SetLayer(3);
	foodStatus = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/UI/food_status.png", Vector2(180, 130)));
	foodStatus->transform->SetScale(0.8f, 0.8f);
	foodStatus->renderer->SetLayer(3);

	for (int i = 0; i < 10; i++)
	{
		waterPoint[i] = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/UI/water_point.png", Vector2(98.7f + i * 22.6f, 50)));
		waterPoint[i]->transform->SetScale(0.8f, 0.8f);
		waterPoint[i]->renderer->SetLayer(3);
		foodPoint[i] = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/UI/food_point.png", Vector2(100.2f + i * 22.5f, 130)));
		foodPoint[i]->transform->SetScale(0.8f, 0.8f);
		foodPoint[i]->renderer->SetLayer(3);
		woodPoint[i] = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/UI/wood_icon.png", Vector2(70.f + i * 25.f, 180)));
		woodPoint[i]->transform->SetScale(0.7f, 0.7f);
		woodPoint[i]->renderer->SetLayer(3);
	}

	Notify();
}

CharacterStatusUI::~CharacterStatusUI()
{

}

void CharacterStatusUI::Notify()
{
	if (waterValue > 10)
		waterValue = 10;
	if (foodValue > 10)
		foodValue = 10;
	if (woodValue > 10)
		woodValue = 10;

	for (int i = 0; i < 10; i++)
	{
		if (i < waterValue)
			waterPoint[i]->SetActive(true);
		else
			waterPoint[i]->SetActive(false);

		if (i < foodValue)
			foodPoint[i]->SetActive(true);
		else
			foodPoint[i]->SetActive(false);

		if (i < woodValue)
			woodPoint[i]->SetActive(true);
		else
			woodPoint[i]->SetActive(false);
	}

	if (waterValue <= 0 || foodValue <= 0)
	{
		Scene::ChangeScene(new GameOverScene());
	}
}
