#include "stdafx.h"
#include "NoAntUI.h"


NoAntUI::NoAntUI() :
	GameObject(L"resources/sprites/UI/alert_no_ant.png", Vector2(1464.f / 2 + 21, 824.f / 2 + 23))
{
	renderer->SetLayer(3);
}


NoAntUI::~NoAntUI()
{

}

void NoAntUI::Update()
{
	renderer->SetAlpha(renderer->GetAlpha() - 0.01f);
	if (renderer->GetAlpha() <= 0.f)
	{
		renderer->SetAlpha(1.f);
		SetActive(false);
	}
}

