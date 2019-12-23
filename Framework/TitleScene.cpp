#include "stdafx.h"
#include "TitleScene.h"

SoundEvent* TitleScene::se = nullptr;

void TitleScene::Initialize()
{
	background = PushBackGameObject(new GameObject(L"resources/sprites/background/title_background.png", Vector2(WIDTH / 2.f, HEIGHT / 2.f)));
	title = PushBackGameObject(new GameObject(L"resources/sprites/title.png", Vector2(WIDTH / 2.f, 320)));

	startButton = (StartButton*)PushBackGameObject(new StartButton(WIDTH / 2.f, 600));
	tutorialButton = (TutorialButton*)PushBackGameObject(new TutorialButton(WIDTH / 2.f, 800));
	exitButton = (ExitButton*)Scene::GetCurrentScene().PushBackGameObject(new ExitButton(200, HEIGHT - 100));

	if (se == nullptr)
	{
		se = new SoundEvent();
		se->LoadFile(L"resources/sounds/BGM/BGM.mp3", true);
		se->Play();
	}
}