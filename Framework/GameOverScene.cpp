#include "stdafx.h"
#include "GameOverScene.h"
#include "DayManager.h"



void GameOverScene::Initialize()
{

	background = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/background/game_end_background.png", Vector2(WIDTH / 2, HEIGHT / 2)));

	endGameLogo = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/endGame_logo.png", Vector2(WIDTH / 2, HEIGHT / 2 - 50)));
	exitButton = (ExitButton*)Scene::GetCurrentScene().PushBackGameObject(new ExitButton(200, HEIGHT - 100));

	FontObject* str = (FontObject*)Scene::GetCurrentScene().PushBackGameObject(new FontObject(L"버틴 날짜 수 : ", Vector2(WIDTH / 2 - 230, HEIGHT / 2 + 100), 0, Vector2(1, 1), L"Arial", 70, 1, 1, 1, 1, true));
	str->renderer->SetLayer(3);
	_itow_s<4>(DayManager::dayCount, scoreNumber, 10);
	scoreText = (FontObject*)Scene::GetCurrentScene().PushBackGameObject(new FontObject(scoreNumber, Vector2(WIDTH / 2 + 240, HEIGHT / 2 + 110), 0, Vector2(1, 1), L"Arial", 70, 1, 1, 1, 1, true));
	scoreText->renderer->SetLayer(3);

	
}