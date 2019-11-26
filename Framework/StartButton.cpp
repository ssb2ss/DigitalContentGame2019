#include "stdafx.h"
#include "StartButton.h"
#include "InputManager.h"
#include "GameScene.h"

//积己 : 全己格

StartButton::StartButton(float x, float y) :
	Button(L"resources/sprites/button/startButton.png", x, y)
{

}

void StartButton::OnClick()
{
	Scene::ChangeScene(new GameScene());
}