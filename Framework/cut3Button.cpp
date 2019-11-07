#include "stdafx.h"
#include "cut3Button.h"
#include "Scene.h"
#include "TitleScene.h"


cut3Button::cut3Button(float x, float y):Button(L"resources/sprites/cutScene/3.png",x,y)
{

}


cut3Button::~cut3Button()
{
}

void cut3Button::OnClick()
{

	Scene::ChangeScene(new TitleScene());
}