#include "stdafx.h"
#include "DayManager.h"
#include "TimeManager.h"
#include "Scene.h"

int DayManager::dayCount = 1;

DayManager::DayManager()
{
	timeOut = 20.f;

	news = (Newspaper*)Scene::GetCurrentScene().PushBackGameObject(new Newspaper());
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
}//¸ÛÃ»ÀÌÁÖÄO

DayManager::~DayManager()
{

}

void DayManager::Update()
{
	news->NewsChange(dayCount);
	timeAdd += TimeManager::GetDeltaTime();
	if (timeAdd >= timeOut)
	{
		timeCount++;
		if (timeCount > 8)
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
	else if (timeCount == 6)
	{
		ChangeSprite(clock, L"resources/sprites/clocks/clock_3.png");
	}
	else if (timeCount == 7)
	{
		ChangeSprite(clock, L"resources/sprites/clocks/clock_4.png");
	}
	else if (timeCount == 8)
	{
		ChangeSprite(clock, L"resources/sprites/clocks/clock_5.png");
	}
}



void DayManager::ChangeSprite(GameObject* g, const wchar_t* path)
{
	SAFE_DELETE(g->renderer);
	g->renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(path, 0, 0));
	g->renderer->SetLayer(3);
}
