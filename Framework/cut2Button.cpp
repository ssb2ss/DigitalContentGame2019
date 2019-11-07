#include "stdafx.h"
#include "cut2Button.h"
#include "Scene.h"
#include "cut3Button.h"



cut2Button::cut2Button(float x, float y): Button(L"resources/sprites/cutScene/2.png", x,y)
{
}


cut2Button::~cut2Button()
{
}

void cut2Button::OnClick()
{

	Scene::GetCurrentScene().PushBackGameObject(new cut3Button(WIDTH / 2, HEIGHT / 2));
	Scene::GetCurrentScene().Destroy(this);
}
