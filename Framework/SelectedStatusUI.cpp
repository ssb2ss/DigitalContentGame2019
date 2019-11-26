#include "stdafx.h"
#include "SelectedStatusUI.h"
#include "Scene.h"

//积己 : 全己格
//荐沥 : 辫柳快

SelectedStatusUI::SelectedStatusUI() :
	GameObject(L"resources/sprites/UI/status/anthouse_status.png", Vector2(365.f, 972.f))
{
	renderer->SetLayer(3);
	state = StatusUI::ANTHOUSE;

	InitializeStatusValue();
}

SelectedStatusUI::~SelectedStatusUI()
{

}

void SelectedStatusUI::SetState(StatusUI newState)
{
	state = newState;
	switch (state)
	{
	case ANTHOUSE:
		ChangeSprite(L"resources/sprites/UI/status/anthouse_status.png");
		break;
	case UI_BUILD_1:
		ChangeSprite(L"resources/sprites/UI/status/build01_status.png");
		break;
	case UI_BUILD_2:
		ChangeSprite(L"resources/sprites/UI/status/build02_status.png");
		break;
	case UI_BUSH:
		ChangeSprite(L"resources/sprites/UI/status/bush_status.png");
		break;
	case UI_FOOD_1:
		ChangeSprite(L"resources/sprites/UI/status/food01_status.png");
		break;
	case UI_FOOD_2:
		ChangeSprite(L"resources/sprites/UI/status/food02_status.png");
		break;
	case UI_FOOD_3:
		ChangeSprite(L"resources/sprites/UI/status/food03_status.png");
		break;
	case UI_FOOD_4:
		ChangeSprite(L"resources/sprites/UI/status/food04_status.png");
		break;
	case UI_FOOD_5:
		ChangeSprite(L"resources/sprites/UI/status/food05_status.png");
		break;
	case UI_TRASH_1:
		ChangeSprite(L"resources/sprites/UI/status/trash01_status.png");
		break;
	case UI_TRASH_2:
		ChangeSprite(L"resources/sprites/UI/status/trash02_status.png");
		break;
	case UI_TRASH_3:
		ChangeSprite(L"resources/sprites/UI/status/trash03_status.png");
		break;
	case UI_WATER:
		ChangeSprite(L"resources/sprites/UI/status/water_status.png");
		break;
	}

	for (int i = 0; i < 4; i++)
	{
		if (value[state].ant > i)
			valueIcon[0][i]->SetActive(true);
		else
			valueIcon[0][i]->SetActive(false);

		if (value[state].water > i)
			valueIcon[1][i]->SetActive(true);
		else
			valueIcon[1][i]->SetActive(false);

		if (value[state].food > i)
			valueIcon[2][i]->SetActive(true);
		else
			valueIcon[2][i]->SetActive(false);
	}
}

void SelectedStatusUI::ChangeSprite(const wchar_t* path)
{
	SAFE_DELETE(renderer);
	renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(path, 0, 0));
	renderer->SetLayer(3);
}

void SelectedStatusUI::InitializeStatusValue()
{
	value[ANTHOUSE]		= StatusValue();
	value[UI_BUILD_1]	= StatusValue(2, 0, 0, 2);
	value[UI_BUILD_2]	= StatusValue(4, 0, 0, 3);
	value[UI_BUSH]		= StatusValue();
	value[UI_FOOD_1]	= StatusValue(3, 0, 2);
	value[UI_FOOD_2]	= StatusValue(2, 1, 1);
	value[UI_FOOD_3]	= StatusValue(1, 0, 1);
	value[UI_FOOD_4]	= StatusValue(3, 2, 1);
	value[UI_FOOD_5]	= StatusValue(4, 1, 3);
	value[UI_TRASH_1]	= StatusValue(2, 1, 0);
	value[UI_TRASH_2]	= StatusValue(4, 2, 1);
	value[UI_TRASH_3]	= StatusValue(4, 1, 2);
	value[UI_WATER]		= StatusValue(1, 2, 0);

	for (int i = 0; i < 4; i++)
	{
		valueIcon[0][i] = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/UI/ant_icon.png", Vector2(550.f + i * 35.f, 925.f)));
		valueIcon[1][i] = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/UI/water_icon.png", Vector2(550.f + i * 35.f, 970.f)));
		valueIcon[2][i] = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/UI/food_icon.png", Vector2(550.f + i * 35.f, 1015.f)));

		for (int j = 0; j < 3; j++)
		{
			valueIcon[j][i]->renderer->SetLayer(4);
			valueIcon[j][i]->SetActive(false);
		}
	}
}
