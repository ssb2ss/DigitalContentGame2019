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

	const wchar_t* subDay1[20] = { L"resources/sprites/newspaper/day1/1.png", L"resources/sprites/newspaper/day1/2.png",  L"resources/sprites/newspaper/day1/3.png",
							 L"resources/sprites/newspaper/day1/4.png",  L"resources/sprites/newspaper/day1/5.png", L"resources/sprites/newspaper/day1/6.png", L"resources/sprites/newspaper/day1/7.png" };
	const wchar_t* subDay2[20] = { L"resources/sprites/newspaper/day2/1.png", L"resources/sprites/newspaper/day2/2.png",  L"resources/sprites/newspaper/day2/3.png",
							 L"resources/sprites/newspaper/day2/4.png",  L"resources/sprites/newspaper/day2/5.png", L"resources/sprites/newspaper/day2/6.png", L"resources/sprites/newspaper/day2/7.png",
							 L"resources/sprites/newspaper/day2/8.png", L"resources/sprites/newspaper/day2/9.png" };
	const wchar_t* subDay3[20] = { L"resources/sprites/newspaper/day3/1.png", L"resources/sprites/newspaper/day3/2.png",  L"resources/sprites/newspaper/day3/3.png",
							 L"resources/sprites/newspaper/day3/4.png",  L"resources/sprites/newspaper/day3/5.png" };
	const wchar_t* subDay4[20] = { L"resources/sprites/newspaper/day4/1.png", L"resources/sprites/newspaper/day4/2.png",  L"resources/sprites/newspaper/day4/3.png",
							 L"resources/sprites/newspaper/day4/4.png" };
	

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

