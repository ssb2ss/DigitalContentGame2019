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

	const wchar_t* subDay1[20] = { L"resources/sprites/newspaper/day1/ant_ghost.png",L"resources/sprites/newspaper/day1/container_food.png",L"resources/sprites/newspaper/day1/container_water.png"
									,L"resources/sprites/newspaper/day1/grasshopper.png",L"resources/sprites/newspaper/day1/light.png",L"resources/sprites/newspaper/day1/picnic.png"
									,L"resources/sprites/newspaper/day1/play.png",L"resources/sprites/newspaper/day1/snack_party.png",L"resources/sprites/newspaper/day1/stone.png"
									,L"resources/sprites/newspaper/day1/vegetarian.png",L"resources/sprites/newspaper/day1/wind.png" };
	const wchar_t* subDay2[20] = { L"resources/sprites/newspaper/day2/ant_ghost.png",L"resources/sprites/newspaper/day2/bread.png",L"resources/sprites/newspaper/day2/cold.png"
									,L"resources/sprites/newspaper/day2/construction.png",L"resources/sprites/newspaper/day2/container_food.png",L"resources/sprites/newspaper/day2/container_water.png"
									,L"resources/sprites/newspaper/day2/cotton.png",L"resources/sprites/newspaper/day2/fishing.png",L"resources/sprites/newspaper/day2/light.png"
									,L"resources/sprites/newspaper/day2/mart_sale.png",L"resources/sprites/newspaper/day2/movie.png",L"resources/sprites/newspaper/day2/pasta"
									,L"resources/sprites/newspaper/day2/snack"};
	const wchar_t* subDay3[20] = { L"resources/sprites/newspaper/day3/airpod.png",L"resources/sprites/newspaper/day3/cockroach.png",L"resources/sprites/newspaper/day3/construction.png"
									,L"resources/sprites/newspaper/day3/construction_stone.png",L"resources/sprites/newspaper/day3/container_trash.png",L"resources/sprites/newspaper/day3/mask.png"
									,L"resources/sprites/newspaper/day3/movie.png",L"resources/sprites/newspaper/day3/no_construction.png",L"resources/sprites/newspaper/day3/pasta.png"
									,L"resources/sprites/newspaper/day3/pizza.png",L"resources/sprites/newspaper/day3/shop.png",L"resources/sprites/newspaper/day3/wind.png"};
	const wchar_t* subDay4[20] = { L"resources/sprites/newspaper/day4/cockroach.png",L"resources/sprites/newspaper/day4/construction_stone.png",L"resources/sprites/newspaper/day4/construction_trash.png"
									,L"resources/sprites/newspaper/day4/container_trash.png",L"resources/sprites/newspaper/day4/drink.png",L"resources/sprites/newspaper/day4/icecream.png"
									,L"resources/sprites/newspaper/day4/mask.png",L"resources/sprites/newspaper/day4/wind.png"};
	

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

