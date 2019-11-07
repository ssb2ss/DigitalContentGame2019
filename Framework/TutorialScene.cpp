#include "stdafx.h"
#include "TutorialScene.h"
#include "cut1Button.h"



void TutorialScene::Initialize()
{
	PushBackGameObject(new cut1Button(WIDTH / 2, HEIGHT / 2));
}