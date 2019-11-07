#include "stdafx.h"
#include "cut1Button.h"
#include "Scene.h"
#include "cut2Button.h"

cut1Button::cut1Button(float x, float y):Button(L"resources/sprites/cutScene/1.png", x,y)
{

}


cut1Button::~cut1Button()
{
}


void cut1Button::OnClick()
{
	Scene::GetCurrentScene().PushBackGameObject(new cut2Button(WIDTH / 2, HEIGHT / 2));
	Scene::GetCurrentScene().Destroy(this);
	
}
