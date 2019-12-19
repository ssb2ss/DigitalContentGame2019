#include "stdafx.h"
#include "Ping.h"

Ping::Ping() :
	GameObject(L"resources/sprites/UI/ping.png", Vector2(0, 0)), x(0), y(0)
{
	renderer->SetLayer(3);
	renderer->SetAlpha(0.f);
	transform->SetScale(0.8f, 0.8f);
	transform->positioningCenter = Vector2(0.f, 34.f);
	SetActive(false);
}

Ping::~Ping()
{

}

void Ping::Update()
{
	renderer->SetAlpha(renderer->GetAlpha() - 0.01f);
	if (renderer->GetAlpha() <= 0.f)
	{
		renderer->SetAlpha(0.f);
		SetActive(false);
	}
}
