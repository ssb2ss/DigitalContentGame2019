#include "stdafx.h"
#include "TutorialButton.h"
#include "GameScene.h"
#include "InputManager.h"
#include "TutorialScene.h"

//생성 : 이주형

TutorialButton::TutorialButton(float x, float y) :
	Button(L"resources/sprites/button/tutorialButton.png", x, y)
{

}


TutorialButton::~TutorialButton()
{
}


void TutorialButton::OnClick()
{
	Scene::ChangeScene(new TutorialScene());
}
