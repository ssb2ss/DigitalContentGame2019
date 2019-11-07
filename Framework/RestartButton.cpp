#include "stdafx.h"
#include "RestartButton.h"
#include "Scene.h"
#include "TitleScene.h"

RestartButton::RestartButton(float x, float y):Button(L"resources/sprites/button/restartButton.png",x,y)
{

}


RestartButton::~RestartButton()
{
}


void RestartButton::OnClick()
{
	Scene::ChangeScene(new TitleScene());
}