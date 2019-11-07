#include "stdafx.h"
#include "DayManager.h"
#include "TimeManager.h"
#include "Scene.h"
#include "GameScene2.h"

int DayManager::dayCount = 1;

DayManager::DayManager()
{
	dayCount = 1;

	timeOut = 2.f;

	news = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/news/stage1_1.png", Vector2(1712, HEIGHT / 2)));
	news->renderer->SetLayer(3);
	clock = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/clocks/clock_9.png", Vector2(1404, 824)));
	clock->renderer->SetLayer(3);
	
	timeCount = 0;
	timeAdd = 0;

	isFade = false;
	isAlphaUp = true;
	fade = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/fade.png", Vector2(WIDTH / 2, HEIGHT / 2)));
	fade->renderer->SetLayer(4);
	fade->renderer->SetAlpha(0.f);
}

DayManager::~DayManager()
{

}

void DayManager::Update()
{
	timeAdd += TimeManager::GetDeltaTime();
	if (timeAdd >= timeOut)
	{
		timeCount++;
		if (timeCount >= 6)
		{
			dayCount++;
			isFade = true;
			timeCount = 5;
		}
		ClockFlick();
		timeAdd = 0;
	}

	if (isFade)
	{
		if (isAlphaUp)
		{
			fade->renderer->SetAlpha(fade->renderer->GetAlpha() + 0.01f);
			if (fade->renderer->GetAlpha() >= 1)
			{
				fade->renderer->SetAlpha(1.f);
				ScreenFlick();
				timeCount = 0;
				ClockFlick();
				timeAdd = 0;
				isAlphaUp = false;
			}
		}
		else
		{
			fade->renderer->SetAlpha(fade->renderer->GetAlpha() - 0.01f);
			if (fade->renderer->GetAlpha() <= 0)
			{
				fade->renderer->SetAlpha(0.f);
				timeAdd = 0;
				isAlphaUp = true;
				isFade = false;
			}
		}
	}
}

void DayManager::ClockFlick()
{
	if (timeCount == 0)
	{
		ChangeSprite(clock, L"resources/sprites/clocks/clock_9.png");
	}
	else if (timeCount == 1)
	{
		ChangeSprite(clock, L"resources/sprites/clocks/clock_10.png");
	}
	else if (timeCount == 2)
	{
		ChangeSprite(clock, L"resources/sprites/clocks/clock_11.png");
	}
	else if (timeCount == 3)
	{
		ChangeSprite(clock, L"resources/sprites/clocks/clock_12.png");
	}
	else if (timeCount == 4)
	{
		ChangeSprite(clock, L"resources/sprites/clocks/clock_1.png");
	}
	else if (timeCount == 5)
	{
		ChangeSprite(clock, L"resources/sprites/clocks/clock_2.png");
	}
}

void DayManager::ScreenFlick()
{
	if (dayCount == 1)
	{
		ChangeSprite(news, L"resources/sprites/news/stage1_1.png");
	}
	else if (dayCount == 2)
	{
		ChangeSprite(news, L"resources/sprites/news/stage1_2.png");
	}
	else if (dayCount == 3)
	{
		ChangeSprite(news, L"resources/sprites/news/stage1_3.png");
	}
	else if (dayCount == 4)
	{
		ChangeSprite(news, L"resources/sprites/news/stage1_4.png");
	}
	else if (dayCount == 5)
	{
		Scene::ChangeScene(new GameScene2());
	}
}


void DayManager::ChangeSprite(GameObject* g, const wchar_t* path)
{
	SAFE_DELETE(g->renderer);
	g->renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(path, 0, 0));
	g->renderer->SetLayer(3);
}
