#include "stdafx.h"
#include "GameScene.h"
#include "FootPrint.h"



void GameScene::Initialize()
{
	GameObject* background = PushBackGameObject(new GameObject(L"resources/sprites/background/game_background_02.png", Vector2(WIDTH / 2, HEIGHT / 2)));
	background->renderer->SetLayer(3);

	gameManager = (GameManager*)PushBackGameObject(new GameManager());


	//GameObject* grid = PushBackGameObject(new GameObject(L"resources/sprites/grid.png", Vector2(772.f, 452.f)));
	//grid->renderer->SetAlpha(0.5f);
}