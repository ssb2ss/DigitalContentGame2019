#include "stdafx.h"
#include "GameScene2.h"


void GameScene2::Initialize()
{
	background = PushBackGameObject(new GameObject(L"resources/sprites/background/map_1.png", Vector2(WIDTH / 2, HEIGHT / 2)));
	std::cout << "여기까지 만들었습니다" << std::endl;
}


