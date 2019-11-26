#include "stdafx.h"
#include "CutImage.h"
#include "InputManager.h"
#include "Scene.h"
#include "TitleScene.h"

//积己 : 捞林屈
//荐沥 : 全己格

CutImage::CutImage() :
	GameObject(L"resources/sprites/cutScene/1.png", Vector2(WIDTH / 2, HEIGHT / 2))
{
	index = 0;
}


CutImage::~CutImage()
{

}

void CutImage::Update()
{
	if (InputManager::GetKeyDown(VK_LBUTTON))
	{
		index++;
		if (index == 1)
		{
			SAFE_DELETE(renderer);
			renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/cutScene/2.png", 0, 0));
		}
		else if (index == 2)
		{
			SAFE_DELETE(renderer);
			renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(L"resources/sprites/cutScene/3.png", 0, 0));
		}
		else
		{
			Scene::ChangeScene(new TitleScene());
		}
	}
}
