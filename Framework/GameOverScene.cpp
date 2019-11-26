#include "stdafx.h"
#include "GameOverScene.h"

//생성 : 이주형

void GameOverScene::Initialize()
{
		
	background = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/background/game_end_background.png", Vector2(WIDTH / 2, HEIGHT / 2)));

	endGameLogo = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/endGame_logo.png", Vector2(WIDTH/2, HEIGHT/2-50)));
	exitButton =(ExitButton*)Scene::GetCurrentScene().PushBackGameObject(new ExitButton(200, HEIGHT-100));

	//restartButton = (RestartButton*)Scene::GetCurrentScene().PushBackGameObject(new RestartButton(200, HEIGHT-300));

	
}