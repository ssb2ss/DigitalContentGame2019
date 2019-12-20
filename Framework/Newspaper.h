#pragma once
#include "GameObject.h"

class Newspaper :
	public GameObject
{
	
	GameObject *newsOutline;
	GameObject *mainPage;
	GameObject *sub1;
	GameObject *sub2;
	GameObject *sub3;


	const wchar_t * mainPageList[10] = { L"resources/sprites/newspaper/b1.png", L"resources/sprites/newspaper/b2.png",  L"resources/sprites/newspaper/b3.png"};

	const wchar_t* subDay1[20] = { L"resources/sprites/newspaper/1.png", L"resources/sprites/newspaper/2.png",  L"resources/sprites/newspaper/3.png",
							 L"resources/sprites/newspaper/5.png",  L"resources/sprites/newspaper/6.png" };
	const wchar_t* subDay2[20] = { L"resources/sprites/newspaper/1.png", L"resources/sprites/newspaper/2.png",  L"resources/sprites/newspaper/3.png",
							 L"resources/sprites/newspaper/5.png",  L"resources/sprites/newspaper/6.png" };
	const wchar_t* subDay3[20] = { L"resources/sprites/newspaper/1.png", L"resources/sprites/newspaper/2.png",  L"resources/sprites/newspaper/3.png",
							 L"resources/sprites/newspaper/5.png",  L"resources/sprites/newspaper/6.png" };
	const wchar_t* subDay4[20] = { L"resources/sprites/newspaper/1.png", L"resources/sprites/newspaper/2.png",  L"resources/sprites/newspaper/3.png",
							 L"resources/sprites/newspaper/5.png",  L"resources/sprites/newspaper/6.png" };
	

	int dayChangeCheck;
	int mainCheck;
public:
	int sub1Cnt;
	int sub2Cnt;
	int sub3Cnt;

	Newspaper();
	~Newspaper();

	void NewsChange(int day);
	void RandomPick();
	void SetNews();

	void ChangeSprite(GameObject* g, const wchar_t* path);


	
};

