#include "stdafx.h"
#include "GameScene.h"
#include "FootPrint.h"

void GameScene::Initialize()
{
	GameObject* background = PushBackGameObject(new GameObject(L"resources/sprites/background/game_background_01.png", Vector2(WIDTH / 2, HEIGHT / 2)));
	background->renderer->SetLayer(0);
	GameObject* mapBackground = PushBackGameObject(new GameObject(L"resources/sprites/background/map_1_night1.png", Vector2(772.f, 452.f)));
	mapBackground->renderer->SetLayer(0);

	gameManager = (GameManager*)PushBackGameObject(new GameManager());


	//GameObject* grid = PushBackGameObject(new GameObject(L"resources/sprites/grid.png", Vector2(772.f, 452.f)));
	//grid->renderer->SetAlpha(0.5f);
}