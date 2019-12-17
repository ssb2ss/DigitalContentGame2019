#include "stdafx.h"
#include "GameScene2.h"

#include "ExitButton.h"



void GameScene2::Initialize()
{
	background = PushBackGameObject(new GameObject(L"resources/sprites/background/map_1.png", Vector2(WIDTH / 2, HEIGHT / 2)));
	GameObject* clearLogo = PushBackGameObject(new GameObject(L"resources/sprites/clear_logo.png", Vector2(WIDTH / 2, HEIGHT / 2)));
	ExitButton* exitButton = (ExitButton*)Scene::GetCurrentScene().PushBackGameObject(new ExitButton(200, HEIGHT - 100));
}


