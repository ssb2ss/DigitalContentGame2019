#include "stdafx.h"
#include "GameManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "GameOverScene.h"

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::GetInstance()
{
	return instance;
}

GameManager::GameManager()
{
	if (instance == nullptr)
	{
		instance = this;
	}
	else
	{
		Scene::GetCurrentScene().Destroy(this);
	}

	mapBackground = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/background/bigmap_1.png", Vector2(772.f, 452.f)));
	mapBackground->renderer->SetLayer(0);
	gridBG = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/biggrid.png", Vector2(772.f, 452.f)));
	gridBG->renderer->SetLayer(0);
	gridBG->renderer->SetAlpha(0.5f);

	SetObstacle(1);

	antManager = (AntManager*)Scene::GetCurrentScene().PushBackGameObject(new AntManager());
	enemyManager = (EnemyManager*)Scene::GetCurrentScene().PushBackGameObject(new EnemyManager());

	fightManager = (FightManager*)Scene::GetCurrentScene().PushBackGameObject(new FightManager());
	antHouse = (AntHouse*)Scene::GetCurrentScene().PushBackGameObject(new AntHouse(120, 67));

	GameObject* selectedStatus_basic = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/UI/status/basic_status.png", Vector2(365.f, 972.f)));
	selectedStatus_basic->renderer->SetLayer(3);

	dayManager = (DayManager*)Scene::GetCurrentScene().PushBackGameObject(new DayManager());
	objectManager = (ObjectManager*)Scene::GetCurrentScene().PushBackGameObject(new ObjectManager());
	charStatus = (CharacterStatusUI*)Scene::GetCurrentScene().PushBackGameObject(new CharacterStatusUI());
	selectedStatus = (SelectedStatusUI*)Scene::GetCurrentScene().PushBackGameObject(new SelectedStatusUI());
	selectedButton = (SelectedButton*)Scene::GetCurrentScene().PushBackGameObject(new SelectedButton(1350, 972));

	FontObject* str = (FontObject*)Scene::GetCurrentScene().PushBackGameObject(new FontObject(L"³²Àº °³¹Ì : ", Vector2(1620, 20), 0, Vector2(1, 1), L"Arial", 30, 1, 1, 1, 1, true));
	str->renderer->SetLayer(3);
	_itow_s<4>(antManager->antList.size(), antNumber, 10);
	antNumberText = (FontObject*)Scene::GetCurrentScene().PushBackGameObject(new FontObject(antNumber, Vector2(1780, 25), 0, Vector2(1, 1), L"Arial", 30, 1, 1, 1, 1, true));
	antNumberText->renderer->SetLayer(3);

	FontObject* str2 = (FontObject*)Scene::GetCurrentScene().PushBackGameObject(new FontObject(L"DAY ", Vector2(1340, 870), 0, Vector2(1, 1), L"Arial", 50, 1, 1, 1, 1, true));
	str2->renderer->SetLayer(3);
	_itow_s<4>(DayManager::dayCount, dayNumber, 10);
	dayNumberText = (FontObject*)Scene::GetCurrentScene().PushBackGameObject(new FontObject(dayNumber, Vector2(1455, 870), 0, Vector2(1, 1), L"Arial", 50, 1, 1, 1, 1, true));
	dayNumberText->renderer->SetLayer(3);

	houseupButton = (PlusButton*)Scene::GetCurrentScene().PushBackGameObject(new PlusButton(815, 972, 0));
	antaddButton = (PlusButton*)Scene::GetCurrentScene().PushBackGameObject(new PlusButton(1015, 972, 1));

	selectedStatus->SetActive(false);
	selectedButton->SetActive(false);

	oldX = curX = InputManager::GetMouseX();
	oldY = curY = InputManager::GetMouseY();

	ping = (Ping*)Scene::GetCurrentScene().PushBackGameObject(new Ping());

	drag = Scene::GetCurrentScene().PushBackGameObject(new GameObject(L"resources/sprites/UI/drag.png"));
	drag->renderer->SetLayer(3);
	drag->renderer->SetAlpha(0.5f);
	drag->transform->SetPosition(0.f, 0.f);
	drag->transform->SetScale(0.f, 0.f);
	drag->SetActive(false);
	dragX = dragY = 0;

	noAnt = (NoAntUI*)Scene::GetCurrentScene().PushBackGameObject(new NoAntUI());
	noAnt->SetActive(false);

	tempBush = nullptr;

	currentDay = 1;

	cameraPos = Vector2(0, 0);
	cameraSpeed = 20.f;

	mapCheck = 0;




}

GameManager::~GameManager()
{

}

void GameManager::Update()
{

	CheckMouseAction();
	ManageAnt();
	ManageDay();
	ManageCamera();
	ChangeDay();
	OnMapChange();

	if (InputManager::GetKeyDown(VK_LBUTTON))
	{
		Vector2 m = InputManager::GetMouseVector2();
		if (m.x - 40 >= 0 && m.x - 40 <= 1464 && m.y - 40 >= 0 && m.y - 40 <= 824)
			std::cout << "x : " << GetPosGridX(m) << " , y : " << GetPosGridY(m) << std::endl;
	}

}

Vector2 GameManager::GetGridPos(int x, int y)
{
	Vector2 res;

	res.x = x * GRID_SIZE;
	res.x -= 2096 + cameraPos.x;
	res.y = y * GRID_SIZE;
	res.y -= 1156 + cameraPos.y;

	return res;
}

int GameManager::GetPosGridX(Vector2 pos)
{
	float x = pos.x;
	x += 2108 + cameraPos.x;
	int res = x / GRID_SIZE;
	return res;
}

int GameManager::GetPosGridX(float _x)
{
	float x = _x;
	x += 2108 + cameraPos.x;
	int res = x / GRID_SIZE;
	return res;
}

int GameManager::GetPosGridY(Vector2 pos)
{
	float y = pos.y;
	y += 1168 + cameraPos.y;
	int res = y / GRID_SIZE;
	return res;
}

int GameManager::GetPosGridY(float _y)
{
	float y = _y;
	y += 1168 + cameraPos.y;
	int res = y / GRID_SIZE;
	return res;
}

void GameManager::OnMapChange()
{
	if (DayManager::dayCount == 4 && mapCheck == 0)
	{
		SpriteChange(mapBackground, L"resources/sprites/background/bigmap_2.png");
		mapCheck++;
		SetObstacle(2);
	}
	else if (DayManager::dayCount == 8 && mapCheck == 1)
	{
		SpriteChange(mapBackground, L"resources/sprites/background/bigmap_3.png");
		mapCheck++;
		SetObstacle(3);
	}
	else if (DayManager::dayCount == 12 && mapCheck == 2)
	{
		SpriteChange(mapBackground, L"resources/sprites/background/bigmap_4.png");
		mapCheck++;
		SetObstacle(4);
	}

}

void GameManager::SetObstacle(int map)
{

	for (int i = 0; i < X_SIZE; i++)
		for (int j = 0; j < Y_SIZE; j++)
			if (GridManager::grid[i][j] == Grid::OBSTACLE)
				GridManager::grid[i][j] = Grid::EMPTY;

	//¸Ê¿¡ µû¸¥ ±×¸®µå ¼³Á¤
	if (map == 1)
	{
		//Çê°£
		for (int i = 133; i <= 143; i++)
			for (int j = 0; j <= 24; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 75; i <= 76; i++)
			for (int j = 0; j <= 20; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 75; i <= 97; i++)
			for (int j = 21; j <= 22; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 118; i <= 143; i++)
			for (int j = 22; j <= 23; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 21; i++)
			GridManager::grid[143][i] = Grid::OBSTACLE;
		for (int i = 124; i <= 142; i++)
			for (int j = 0; j <= 1; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 125; i <= 142; i++)
			GridManager::grid[i][2] = Grid::OBSTACLE;
		for (int i = 126; i <= 142; i++)
			GridManager::grid[i][3] = Grid::OBSTACLE;
		for (int i = 133; i <= 142; i++)
			for (int j = 4; j <= 5; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;	
		for (int i = 134; i <= 142; i++)
			for (int j = 21; j <= 24; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 131; i <= 133; i++)
			for (int j = 8; j <= 21; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 125; i <= 130; i++)
			for (int j = 13; j <= 18; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 77; i <= 92; i++)
			for (int j = 0; j <= 20; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 93; i <= 94; i++)
			for (int j = 2; j <= 11; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 95; i <= 96; i++)
			for (int j = 5; j <= 10; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 97; i <= 99; i++)
			GridManager::grid[i][10] = Grid::OBSTACLE;
		for (int i = 99; i <= 101; i++)
			GridManager::grid[i][11] = Grid::OBSTACLE;
		for (int i = 101; i <= 103; i++)
			GridManager::grid[i][12] = Grid::OBSTACLE;
		for (int i = 103; i <= 105; i++)
			GridManager::grid[i][13] = Grid::OBSTACLE;
		for (int i = 105; i <= 106; i++)
			GridManager::grid[i][14] = Grid::OBSTACLE;

		//½£
		for (int i = 0; i <= 54; i++)
			for (int j = 0; j <= 8; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 55; i++)
			GridManager::grid[i][9] = Grid::OBSTACLE;
		for (int i = 0; i <= 56; i++)
			GridManager::grid[i][10] = Grid::OBSTACLE;
		for (int i = 0; i <= 57; i++)
			for (int j = 11; j <= 12; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 58; i++)
			for (int j = 13; j <= 15; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 59; i++)
			for (int j = 16; j <= 19; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 60; i++)
			for (int j = 20; j <= 28; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 59; i++)
			GridManager::grid[i][29] = Grid::OBSTACLE;
		for (int i = 0; i <= 58; i++)
			GridManager::grid[i][30] = Grid::OBSTACLE;
		for (int i = 0; i <= 57; i++)
			GridManager::grid[i][31] = Grid::OBSTACLE;
		for (int i = 0; i <= 56; i++)
			GridManager::grid[i][32] = Grid::OBSTACLE;
		for (int i = 0; i <= 54; i++)
			GridManager::grid[i][33] = Grid::OBSTACLE;
		for (int i = 0; i <= 53; i++)
			for (int j = 34; j <= 47; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 54; i++)
			for (int j = 48; j <= 50; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 55; i++)
			for (int j = 51; j <= 61; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 53; i++)
			for (int j = 62; j <= 64; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 47; i++)
			GridManager::grid[i][65] = Grid::OBSTACLE;
		for (int i = 0; i <= 46; i++)
			GridManager::grid[i][66] = Grid::OBSTACLE;
		for (int i = 0; i <= 45; i++)
			GridManager::grid[i][67] = Grid::OBSTACLE;
		for (int i = 0; i <= 40; i++)
			GridManager::grid[i][68] = Grid::OBSTACLE;
		for (int i = 0; i <= 39; i++)
			GridManager::grid[i][69] = Grid::OBSTACLE;
		for (int i = 0; i <= 38; i++)
			GridManager::grid[i][70] = Grid::OBSTACLE;
		for (int i = 0; i <= 37; i++)
			GridManager::grid[i][71] = Grid::OBSTACLE;
		for (int i = 4; i <= 16; i++)
			GridManager::grid[i][72] = Grid::OBSTACLE;
		for (int i = 6; i <= 11; i++)
			for (int j = 73; j <= 75; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//¿¬¸ø
		for (int i = 0; i <= 6; i++)
			GridManager::grid[i][101] = Grid::OBSTACLE;
		for (int i = 0; i <= 9; i++)
			GridManager::grid[i][102] = Grid::OBSTACLE;
		for (int i = 0; i <= 12; i++)
			GridManager::grid[i][103] = Grid::OBSTACLE;
		for (int i = 0; i <= 14; i++)
			GridManager::grid[i][104] = Grid::OBSTACLE;
		for (int i = 0; i <= 15; i++)
			GridManager::grid[i][105] = Grid::OBSTACLE;
		for (int i = 0; i <= 16; i++)
			GridManager::grid[i][106] = Grid::OBSTACLE;
		for (int i = 0; i <= 18; i++)
			GridManager::grid[i][107] = Grid::OBSTACLE;
		for (int i = 0; i <= 19; i++)
			GridManager::grid[i][108] = Grid::OBSTACLE;
		for (int i = 0; i <= 20; i++)
			GridManager::grid[i][109] = Grid::OBSTACLE;
		for (int i = 0; i <= 21; i++)
			GridManager::grid[i][110] = Grid::OBSTACLE;
		for (int i = 0; i <= 22; i++)
			GridManager::grid[i][111] = Grid::OBSTACLE;
		for (int i = 0; i <= 23; i++)
			for (int j = 112; j <= 113; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 24; i++)
			GridManager::grid[i][114] = Grid::OBSTACLE;
		for (int i = 0; i <= 24; i++)
			GridManager::grid[i][115] = Grid::OBSTACLE;
		for (int i = 0; i <= 25; i++)
			for (int j = 116; j <= 117; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 26; i++)
			for (int j = 118; j <= 119; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 27; i++)
			for (int j = 120; j <= 122; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 28; i++)
			for (int j = 123; j <= 125; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 29; i++)
			for (int j = 126; j <= 129; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 30; i++)
			for (int j = 130; j <= 134; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//µµ¶û ¹Û
		for (int i = 157; i <= 239; i++)
			for (int j = 0; j <= 134; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 34; i <= 134; i++)
			GridManager::grid[156][i] = Grid::OBSTACLE;
		for (int i = 58; i <= 134; i++)
			GridManager::grid[155][i] = Grid::OBSTACLE;

	}
	else if (map == 2)
	{
		//Çê°£
		for (int i = 133; i <= 143; i++)
			for (int j = 0; j <= 24; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 75; i <= 76; i++)
			for (int j = 0; j <= 20; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 75; i <= 97; i++)
			for (int j = 21; j <= 22; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 118; i <= 143; i++)
			for (int j = 22; j <= 23; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 21; i++)
			GridManager::grid[143][i] = Grid::OBSTACLE;
		for (int i = 124; i <= 142; i++)
			for (int j = 0; j <= 1; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 125; i <= 142; i++)
			GridManager::grid[i][2] = Grid::OBSTACLE;
		for (int i = 126; i <= 142; i++)
			GridManager::grid[i][3] = Grid::OBSTACLE;
		for (int i = 133; i <= 142; i++)
			for (int j = 4; j <= 5; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 134; i <= 142; i++)
			for (int j = 21; j <= 24; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 131; i <= 133; i++)
			for (int j = 8; j <= 21; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 125; i <= 130; i++)
			for (int j = 13; j <= 18; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 77; i <= 92; i++)
			for (int j = 0; j <= 20; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 93; i <= 94; i++)
			for (int j = 2; j <= 11; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 95; i <= 96; i++)
			for (int j = 5; j <= 10; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 97; i <= 99; i++)
			GridManager::grid[i][10] = Grid::OBSTACLE;
		for (int i = 99; i <= 101; i++)
			GridManager::grid[i][11] = Grid::OBSTACLE;
		for (int i = 101; i <= 103; i++)
			GridManager::grid[i][12] = Grid::OBSTACLE;
		for (int i = 103; i <= 105; i++)
			GridManager::grid[i][13] = Grid::OBSTACLE;
		for (int i = 105; i <= 106; i++)
			GridManager::grid[i][14] = Grid::OBSTACLE;

		//½£
		for (int i = 0; i <= 54; i++)
			for (int j = 0; j <= 8; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 55; i++)
			GridManager::grid[i][9] = Grid::OBSTACLE;
		for (int i = 0; i <= 56; i++)
			GridManager::grid[i][10] = Grid::OBSTACLE;
		for (int i = 0; i <= 57; i++)
			for (int j = 11; j <= 12; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 58; i++)
			for (int j = 13; j <= 15; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 59; i++)
			for (int j = 16; j <= 19; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 60; i++)
			for (int j = 20; j <= 28; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 59; i++)
			GridManager::grid[i][29] = Grid::OBSTACLE;
		for (int i = 0; i <= 58; i++)
			GridManager::grid[i][30] = Grid::OBSTACLE;
		for (int i = 0; i <= 57; i++)
			GridManager::grid[i][31] = Grid::OBSTACLE;
		for (int i = 0; i <= 56; i++)
			GridManager::grid[i][32] = Grid::OBSTACLE;
		for (int i = 0; i <= 54; i++)
			GridManager::grid[i][33] = Grid::OBSTACLE;
		for (int i = 0; i <= 53; i++)
			for (int j = 34; j <= 47; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 54; i++)
			for (int j = 48; j <= 50; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 55; i++)
			for (int j = 51; j <= 61; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 53; i++)
			for (int j = 62; j <= 64; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 47; i++)
			GridManager::grid[i][65] = Grid::OBSTACLE;
		for (int i = 0; i <= 46; i++)
			GridManager::grid[i][66] = Grid::OBSTACLE;
		for (int i = 0; i <= 45; i++)
			GridManager::grid[i][67] = Grid::OBSTACLE;
		for (int i = 0; i <= 40; i++)
			GridManager::grid[i][68] = Grid::OBSTACLE;
		for (int i = 0; i <= 39; i++)
			GridManager::grid[i][69] = Grid::OBSTACLE;
		for (int i = 0; i <= 38; i++)
			GridManager::grid[i][70] = Grid::OBSTACLE;
		for (int i = 0; i <= 37; i++)
			GridManager::grid[i][71] = Grid::OBSTACLE;
		for (int i = 4; i <= 16; i++)
			GridManager::grid[i][72] = Grid::OBSTACLE;
		for (int i = 6; i <= 11; i++)
			for (int j = 73; j <= 75; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//¿¬¸ø
		for (int i = 0; i <= 6; i++)
			GridManager::grid[i][101] = Grid::OBSTACLE;
		for (int i = 0; i <= 9; i++)
			GridManager::grid[i][102] = Grid::OBSTACLE;
		for (int i = 0; i <= 12; i++)
			GridManager::grid[i][103] = Grid::OBSTACLE;
		for (int i = 0; i <= 14; i++)
			GridManager::grid[i][104] = Grid::OBSTACLE;
		for (int i = 0; i <= 15; i++)
			GridManager::grid[i][105] = Grid::OBSTACLE;
		for (int i = 0; i <= 16; i++)
			GridManager::grid[i][106] = Grid::OBSTACLE;
		for (int i = 0; i <= 18; i++)
			GridManager::grid[i][107] = Grid::OBSTACLE;
		for (int i = 0; i <= 19; i++)
			GridManager::grid[i][108] = Grid::OBSTACLE;
		for (int i = 0; i <= 20; i++)
			GridManager::grid[i][109] = Grid::OBSTACLE;
		for (int i = 0; i <= 21; i++)
			GridManager::grid[i][110] = Grid::OBSTACLE;
		for (int i = 0; i <= 22; i++)
			GridManager::grid[i][111] = Grid::OBSTACLE;
		for (int i = 0; i <= 23; i++)
			for (int j = 112; j <= 113; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 24; i++)
			GridManager::grid[i][114] = Grid::OBSTACLE;
		for (int i = 0; i <= 24; i++)
			GridManager::grid[i][115] = Grid::OBSTACLE;
		for (int i = 0; i <= 25; i++)
			for (int j = 116; j <= 117; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 26; i++)
			for (int j = 118; j <= 119; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 27; i++)
			for (int j = 120; j <= 122; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 28; i++)
			for (int j = 123; j <= 125; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 29; i++)
			for (int j = 126; j <= 129; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 30; i++)
			for (int j = 130; j <= 134; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//¾²·¹±âÅë
		for (int i = 53; i <= 99; i++)
			for (int j = 100; j <= 134; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 109; i <= 135; i++)
			for (int j = 118; i <= 134; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//µµ¶û
		for (int i = 157; i <= 170; i++)
			for (int j = 0; j <= 48; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 156; i <= 169; i++)
			for (int j = 59; j <= 134; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//ÀÚÀç
		for (int i = 177; i <= 188; i++)
			for (int j = 36; j <= 71; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 189; i <= 190; i++)
			for (int j = 44; j <= 50; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 191; i <= 192; i++)
			for (int j = 48; j <= 55; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 193; i <= 194; i++)
			for (int j = 53; j <= 59; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 195; i <= 196; i++)
			for (int j = 57; j <= 64; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 197; i <= 199; i++)
			for (int j = 62; j <= 68; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 204; i <= 213; i++)
			for (int j = 56; j <= 65; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 214; i <= 230; i++)
			for (int j = 56; j <= 72; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//µµ·Î
		for (int i = 67; i <= 134; i++)
			GridManager::grid[239][i] = Grid::OBSTACLE;
		for (int i = 74; i <= 134; i++)
			GridManager::grid[238][i] = Grid::OBSTACLE;
		for (int i = 77; i <= 134; i++)
			GridManager::grid[237][i] = Grid::OBSTACLE;
		for (int i = 81; i <= 134; i++)
			GridManager::grid[236][i] = Grid::OBSTACLE;
		for (int i = 84; i <= 134; i++)
			GridManager::grid[235][i] = Grid::OBSTACLE;
		for (int i = 87; i <= 134; i++)
			GridManager::grid[234][i] = Grid::OBSTACLE;
		for (int i = 90; i <= 134; i++)
			GridManager::grid[233][i] = Grid::OBSTACLE;
		for (int i = 95; i <= 134; i++)
			GridManager::grid[232][i] = Grid::OBSTACLE;
		for (int i = 96; i <= 134; i++)
			GridManager::grid[231][i] = Grid::OBSTACLE;
		for (int i = 99; i <= 134; i++)
			GridManager::grid[230][i] = Grid::OBSTACLE;
		for (int i = 101; i <= 134; i++)
			GridManager::grid[229][i] = Grid::OBSTACLE;
		for (int i = 102; i <= 134; i++)
			GridManager::grid[228][i] = Grid::OBSTACLE;
		for (int i = 103; i <= 134; i++)
			GridManager::grid[227][i] = Grid::OBSTACLE;
		for (int i = 104; i <= 134; i++)
			GridManager::grid[226][i] = Grid::OBSTACLE;
		for (int i = 107; i <= 134; i++)
			GridManager::grid[225][i] = Grid::OBSTACLE;
		for (int i = 109; i <= 134; i++)
			GridManager::grid[224][i] = Grid::OBSTACLE;
		for (int i = 111; i <= 134; i++)
			GridManager::grid[223][i] = Grid::OBSTACLE;
		for (int i = 113; i <= 134; i++)
			GridManager::grid[222][i] = Grid::OBSTACLE;
		for (int i = 115; i <= 134; i++)
			GridManager::grid[221][i] = Grid::OBSTACLE;
		for (int i = 116; i <= 134; i++)
			GridManager::grid[220][i] = Grid::OBSTACLE;
		for (int i = 118; i <= 134; i++)
			GridManager::grid[219][i] = Grid::OBSTACLE;
		for (int i = 119; i <= 134; i++)
			GridManager::grid[218][i] = Grid::OBSTACLE;
		for (int i = 121; i <= 134; i++)
			GridManager::grid[217][i] = Grid::OBSTACLE;
		for (int i = 122; i <= 134; i++)
			GridManager::grid[216][i] = Grid::OBSTACLE;
		for (int i = 123; i <= 134; i++)
			GridManager::grid[215][i] = Grid::OBSTACLE;
		for (int i = 125; i <= 134; i++)
			GridManager::grid[214][i] = Grid::OBSTACLE;
	}
	else if (map == 3)
	{
		//Çê°£
		for (int i = 75; i <= 97; i++)
			for (int j = 0; i <= 22; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 118; i <= 143; i++)
			for (int j = 22; j <= 24; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 22; i++)
			GridManager::grid[143][i] = Grid::OBSTACLE;
		for (int i = 132; i <= 138; i++)
			for (int j = 11; j <= 17; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//½£
		for (int i = 7; i <= 13; i++)
			for (int j = 25; j <= 29; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 29; i <= 38; i++)
			for (int j = 36; j <= 42; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 8; i <= 13; i++)
			for (int j = 55; j <= 58; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 31; i <= 36; i++)
			for (int j = 69; j <= 72; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//¿¬¸ø
		for (int i = 0; i <= 6; i++)
			GridManager::grid[i][101] = Grid::OBSTACLE;
		for (int i = 0; i <= 9; i++)
			GridManager::grid[i][102] = Grid::OBSTACLE;
		for (int i = 0; i <= 12; i++)
			GridManager::grid[i][103] = Grid::OBSTACLE;
		for (int i = 0; i <= 14; i++)
			GridManager::grid[i][104] = Grid::OBSTACLE;
		for (int i = 0; i <= 15; i++)
			GridManager::grid[i][105] = Grid::OBSTACLE;
		for (int i = 0; i <= 16; i++)
			GridManager::grid[i][106] = Grid::OBSTACLE;
		for (int i = 0; i <= 18; i++)
			GridManager::grid[i][107] = Grid::OBSTACLE;
		for (int i = 0; i <= 19; i++)
			GridManager::grid[i][108] = Grid::OBSTACLE;
		for (int i = 0; i <= 20; i++)
			GridManager::grid[i][109] = Grid::OBSTACLE;
		for (int i = 0; i <= 21; i++)
			GridManager::grid[i][110] = Grid::OBSTACLE;
		for (int i = 0; i <= 22; i++)
			GridManager::grid[i][111] = Grid::OBSTACLE;
		for (int i = 0; i <= 23; i++)
			for (int j = 112; j <= 113; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 24; i++)
			GridManager::grid[i][114] = Grid::OBSTACLE;
		for (int i = 0; i <= 24; i++)
			GridManager::grid[i][115] = Grid::OBSTACLE;
		for (int i = 0; i <= 25; i++)
			for (int j = 116; j <= 117; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 26; i++)
			for (int j = 118; j <= 119; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 27; i++)
			for (int j = 120; j <= 122; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 28; i++)
			for (int j = 123; j <= 125; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 29; i++)
			for (int j = 126; j <= 129; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 30; i++)
			for (int j = 130; j <= 134; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//¾²·¹±âÅë
		for (int i = 51; i <= 102; i++)
			for (int j = 100; j <= 134; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 103; i <= 135; i++)
			for (int j = 113; j <= 134; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//µµ¶û
		for (int i = 157; i <= 170; i++)
			for (int j = 0; j <= 48; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 156; i <= 169; i++)
			for (int j = 59; j <= 134; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//ÀÚÀç
		for (int i = 183; i <= 208; i++)
			for (int j = 50; j <= 84; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 209; i <= 232; i++)
			for (int j = 64; j <= 78; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 217; i <= 234; i++)
			for (int j = 79; j <= 90; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 179; i <= 193; i++)
			for (int j = 22; j <= 36; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 181; i <= 188; i++)
			for (int j = 37; j <= 43; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 189; i <= 193; i++)
			for (int j = 38; j <= 46; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 194; i <= 198; i++)
			for (int j = 41; j <= 50; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 199; i <= 205; i++)
			for (int j = 45; j <= 54; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 216; i <= 239; i++)
			for (int j = 35; j <= 46; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 202; i <= 239; i++)
			for (int j = 0; j <= 26; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//µµ·Î
		for (int i = 67; i <= 134; i++)
			GridManager::grid[239][i] = Grid::OBSTACLE;
		for (int i = 74; i <= 134; i++)
			GridManager::grid[238][i] = Grid::OBSTACLE;
		for (int i = 77; i <= 134; i++)
			GridManager::grid[237][i] = Grid::OBSTACLE;
		for (int i = 81; i <= 134; i++)
			GridManager::grid[236][i] = Grid::OBSTACLE;
		for (int i = 84; i <= 134; i++)
			GridManager::grid[235][i] = Grid::OBSTACLE;
		for (int i = 87; i <= 134; i++)
			GridManager::grid[234][i] = Grid::OBSTACLE;
		for (int i = 90; i <= 134; i++)
			GridManager::grid[233][i] = Grid::OBSTACLE;
		for (int i = 95; i <= 134; i++)
			GridManager::grid[232][i] = Grid::OBSTACLE;
		for (int i = 96; i <= 134; i++)
			GridManager::grid[231][i] = Grid::OBSTACLE;
		for (int i = 99; i <= 134; i++)
			GridManager::grid[230][i] = Grid::OBSTACLE;
		for (int i = 101; i <= 134; i++)
			GridManager::grid[229][i] = Grid::OBSTACLE;
		for (int i = 102; i <= 134; i++)
			GridManager::grid[228][i] = Grid::OBSTACLE;
		for (int i = 103; i <= 134; i++)
			GridManager::grid[227][i] = Grid::OBSTACLE;
		for (int i = 104; i <= 134; i++)
			GridManager::grid[226][i] = Grid::OBSTACLE;
		for (int i = 107; i <= 134; i++)
			GridManager::grid[225][i] = Grid::OBSTACLE;
		for (int i = 109; i <= 134; i++)
			GridManager::grid[224][i] = Grid::OBSTACLE;
		for (int i = 111; i <= 134; i++)
			GridManager::grid[223][i] = Grid::OBSTACLE;
		for (int i = 113; i <= 134; i++)
			GridManager::grid[222][i] = Grid::OBSTACLE;
		for (int i = 115; i <= 134; i++)
			GridManager::grid[221][i] = Grid::OBSTACLE;
		for (int i = 116; i <= 134; i++)
			GridManager::grid[220][i] = Grid::OBSTACLE;
		for (int i = 118; i <= 134; i++)
			GridManager::grid[219][i] = Grid::OBSTACLE;
		for (int i = 119; i <= 134; i++)
			GridManager::grid[218][i] = Grid::OBSTACLE;
		for (int i = 121; i <= 134; i++)
			GridManager::grid[217][i] = Grid::OBSTACLE;
		for (int i = 122; i <= 134; i++)
			GridManager::grid[216][i] = Grid::OBSTACLE;
		for (int i = 123; i <= 134; i++)
			GridManager::grid[215][i] = Grid::OBSTACLE;
		for (int i = 125; i <= 134; i++)
			GridManager::grid[214][i] = Grid::OBSTACLE;
	}
	else if (map == 4)
	{
		//Çê°£
		for (int i = 74; i <= 144; i++)
			for (int j = 0; j <= 20; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//½£
		for (int i = 7; i <= 13; i++)
			for (int j = 25; j <= 29; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 29; i <= 38; i++)
			for (int j = 36; j <= 42; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 8; i <= 13; i++)
			for (int j = 55; j <= 58; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 31; i <= 36; i++)
			for (int j = 69; j <= 72; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//¿¬¸ø
		for (int i = 0; i <= 6; i++)
			GridManager::grid[i][101] = Grid::OBSTACLE;
		for (int i = 0; i <= 9; i++)
			GridManager::grid[i][102] = Grid::OBSTACLE;
		for (int i = 0; i <= 12; i++)
			GridManager::grid[i][103] = Grid::OBSTACLE;
		for (int i = 0; i <= 14; i++)
			GridManager::grid[i][104] = Grid::OBSTACLE;
		for (int i = 0; i <= 15; i++)
			GridManager::grid[i][105] = Grid::OBSTACLE;
		for (int i = 0; i <= 16; i++)
			GridManager::grid[i][106] = Grid::OBSTACLE;
		for (int i = 0; i <= 18; i++)
			GridManager::grid[i][107] = Grid::OBSTACLE;
		for (int i = 0; i <= 19; i++)
			GridManager::grid[i][108] = Grid::OBSTACLE;
		for (int i = 0; i <= 20; i++)
			GridManager::grid[i][109] = Grid::OBSTACLE;
		for (int i = 0; i <= 21; i++)
			GridManager::grid[i][110] = Grid::OBSTACLE;
		for (int i = 0; i <= 22; i++)
			GridManager::grid[i][111] = Grid::OBSTACLE;
		for (int i = 0; i <= 23; i++)
			for (int j = 112; j <= 113; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 24; i++)
			GridManager::grid[i][114] = Grid::OBSTACLE;
		for (int i = 0; i <= 24; i++)
			GridManager::grid[i][115] = Grid::OBSTACLE;
		for (int i = 0; i <= 25; i++)
			for (int j = 116; j <= 117; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 26; i++)
			for (int j = 118; j <= 119; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 27; i++)
			for (int j = 120; j <= 122; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 28; i++)
			for (int j = 123; j <= 125; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 29; i++)
			for (int j = 126; j <= 129; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 0; i <= 30; i++)
			for (int j = 130; j <= 134; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//¾²·¹±âÅë
		for (int i = 51; i <= 102; i++)
			for (int j = 100; j <= 134; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 103; i <= 129; i++)
			for (int j = 113; j <= 134; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//µµ¶û
		for (int i = 157; i <= 170; i++)
			for (int j = 0; j <= 48; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 156; i <= 169; i++)
			for (int j = 59; j <= 134; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//ÀÚÀç
		for (int i = 202; i <= 239; i++)
			for (int j = 0; j <= 14; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 185; i <= 239; i++)
			for (int j = 15; j <= 50; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 219; i <= 237; i++)
			for (int j = 51; j <= 54; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 178; i <= 184; i++)
			for (int j = 42; j <= 70; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 191; i <= 197; i++)
			for (int j = 61; j <= 69; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 198; i <= 202; i++)
			for (int j = 65; j <= 73; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 203; i <= 206; i++)
			for (int j = 69; j <= 76; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 207; i <= 209; i++)
			for (int j = 72; j <= 79; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 210; i <= 215; i++)
			for (int j = 74; j <= 80; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 200; i <= 205; i++)
			for (int j = 92; j <= 97; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 206; i <= 213; i++)
			for (int j = 90; j <= 95; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 214; i <= 220; i++)
			for (int j = 88; j <= 93; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
		for (int i = 221; i <= 227; i++)
			for (int j = 86; j <= 92; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;

		//µµ·Î
		for (int i = 67; i <= 134; i++)
			GridManager::grid[239][i] = Grid::OBSTACLE;
		for (int i = 74; i <= 134; i++)
			GridManager::grid[238][i] = Grid::OBSTACLE;
		for (int i = 77; i <= 134; i++)
			GridManager::grid[237][i] = Grid::OBSTACLE;
		for (int i = 81; i <= 134; i++)
			GridManager::grid[236][i] = Grid::OBSTACLE;
		for (int i = 84; i <= 134; i++)
			GridManager::grid[235][i] = Grid::OBSTACLE;
		for (int i = 87; i <= 134; i++)
			GridManager::grid[234][i] = Grid::OBSTACLE;
		for (int i = 90; i <= 134; i++)
			GridManager::grid[233][i] = Grid::OBSTACLE;
		for (int i = 95; i <= 134; i++)
			GridManager::grid[232][i] = Grid::OBSTACLE;
		for (int i = 96; i <= 134; i++)
			GridManager::grid[231][i] = Grid::OBSTACLE;
		for (int i = 99; i <= 134; i++)
			GridManager::grid[230][i] = Grid::OBSTACLE;
		for (int i = 101; i <= 134; i++)
			GridManager::grid[229][i] = Grid::OBSTACLE;
		for (int i = 102; i <= 134; i++)
			GridManager::grid[228][i] = Grid::OBSTACLE;
		for (int i = 103; i <= 134; i++)
			GridManager::grid[227][i] = Grid::OBSTACLE;
		for (int i = 104; i <= 134; i++)
			GridManager::grid[226][i] = Grid::OBSTACLE;
		for (int i = 107; i <= 134; i++)
			GridManager::grid[225][i] = Grid::OBSTACLE;
		for (int i = 109; i <= 134; i++)
			GridManager::grid[224][i] = Grid::OBSTACLE;
		for (int i = 111; i <= 134; i++)
			GridManager::grid[223][i] = Grid::OBSTACLE;
		for (int i = 113; i <= 134; i++)
			GridManager::grid[222][i] = Grid::OBSTACLE;
		for (int i = 115; i <= 134; i++)
			GridManager::grid[221][i] = Grid::OBSTACLE;
		for (int i = 116; i <= 134; i++)
			GridManager::grid[220][i] = Grid::OBSTACLE;
		for (int i = 118; i <= 134; i++)
			GridManager::grid[219][i] = Grid::OBSTACLE;
		for (int i = 119; i <= 134; i++)
			GridManager::grid[218][i] = Grid::OBSTACLE;
		for (int i = 121; i <= 134; i++)
			GridManager::grid[217][i] = Grid::OBSTACLE;
		for (int i = 122; i <= 134; i++)
			GridManager::grid[216][i] = Grid::OBSTACLE;
		for (int i = 123; i <= 134; i++)
			GridManager::grid[215][i] = Grid::OBSTACLE;
		for (int i = 125; i <= 134; i++)
			GridManager::grid[214][i] = Grid::OBSTACLE;
		for (int i = 208; i <= 223; i++)
			for (int j = 119; j <= 134; j++)
				GridManager::grid[i][j] = Grid::OBSTACLE;
	}
}

void GameManager::CheckMouseAction()
{

	if (tempBush == nullptr)
	{

		if (InputManager::GetKeyDown(VK_LBUTTON))
		{
			for (auto& i : antManager->currentAntGroup)
			{
				i->isSelected = false;
			}
			antManager->currentAntGroup.clear();
			int tempX = InputManager::GetMouseX();
			int tempY = InputManager::GetMouseY();
			tempX -= 40;
			tempY -= 40;
			if (tempX >= 0 && tempX <= 1464 && tempY >= 0 && tempY <= 824)
			{
				tempX += 40;
				tempY += 40;

				drag->SetActive(true);
				dragX = tempX;
				dragY = tempY;
				drag->transform->SetPosition(dragX, dragY);

				oldX = GetPosGridX(tempX);
				oldY = GetPosGridY(tempY);
			}
		}
		else if (InputManager::GetKeyPressed(VK_LBUTTON))
		{
			int tempX = InputManager::GetMouseX();
			int tempY = InputManager::GetMouseY();
			tempX -= 40;
			tempY -= 40;
			if (tempX >= 0 && tempX <= 1464 && tempY >= 0 && tempY <= 824)
			{
				tempX += 40;
				tempY += 40;

				drag->transform->SetPosition((tempX + dragX) / 2.f, (tempY + dragY) / 2.f);
				drag->transform->SetScale((tempX - dragX) / 1464.f, (tempY - dragY) / 816.f);
			}
		}
		else if (InputManager::GetKeyUp(VK_LBUTTON))
		{
			int tempX = InputManager::GetMouseX();
			int tempY = InputManager::GetMouseY();
			tempX -= 40;
			tempY -= 40;
			if (tempX >= 0 && tempX <= 1464 && tempY >= 0 && tempY <= 824)
			{
				tempX += 40;
				tempY += 40;

				curX = GetPosGridX(tempX);
				curY = GetPosGridY(tempY);

				if (curX == oldX && curY == oldY)
				{
					if (GridManager::grid[curX][curY] == Grid::EMPTY || GridManager::grid[curX][curY] == Grid::OBSTACLE)
					{
						selectedStatus->SetState(StatusUI::ANTHOUSE);
						selectedStatus->SetActive(false);
						selectedButton->SetActive(false);
						for (auto& i : antManager->antList)
						{
							if (i->x == curX && i->y == curY)
							{
								antManager->currentAntGroup.push_back(i);
								i->isSelected = true;
								break;
							}
						}
					}
					else if (GridManager::grid[curX][curY] == Grid::HOUSE)
						SetSelectedUI(StatusUI::ANTHOUSE, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::BUILD_1)
						SetSelectedUI(StatusUI::UI_BUILD_1, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::BUILD_2)
						SetSelectedUI(StatusUI::UI_BUILD_2, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::BUILD_3)
						SetSelectedUI(StatusUI::UI_BUILD_3, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::BUSH)
						SetSelectedUI(StatusUI::UI_BUSH, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::FOOD_1)
						SetSelectedUI(StatusUI::UI_FOOD_1, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::FOOD_2)
						SetSelectedUI(StatusUI::UI_FOOD_2, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::FOOD_3)
						SetSelectedUI(StatusUI::UI_FOOD_3, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::FOOD_4)
						SetSelectedUI(StatusUI::UI_FOOD_4, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::FOOD_5)
						SetSelectedUI(StatusUI::UI_FOOD_5, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::FOOD_6)
						SetSelectedUI(StatusUI::UI_FOOD_6, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::FOOD_7)
						SetSelectedUI(StatusUI::UI_FOOD_7, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::FOOD_8)
						SetSelectedUI(StatusUI::UI_FOOD_8, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::FOOD_9)
						SetSelectedUI(StatusUI::UI_FOOD_9, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::FOOD_10)
						SetSelectedUI(StatusUI::UI_FOOD_10, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::TRASH_1)
						SetSelectedUI(StatusUI::UI_TRASH_1, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::TRASH_2)
						SetSelectedUI(StatusUI::UI_TRASH_2, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::TRASH_3)
						SetSelectedUI(StatusUI::UI_TRASH_3, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::TRASH_4)
						SetSelectedUI(StatusUI::UI_TRASH_4, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::TRASH_5)
						SetSelectedUI(StatusUI::UI_TRASH_5, curX, curY);
					else if (GridManager::grid[curX][curY] == Grid::WATER)
						SetSelectedUI(StatusUI::UI_WATER, curX, curY);
				}
				else
				{
					if (curX < oldX)
					{
						int tem = curX;
						curX = oldX;
						oldX = tem;
					}
					if (curY < oldY)
					{
						int tem = curY;
						curY = oldY;
						oldY = tem;
					}

					for (int i = oldX; i <= curX; i++)
					{
						for (int j = oldY; j <= curY; j++)
						{
							for (auto& a : antManager->antList)
							{
								if (a->x == i && a->y == j && !a->isCarrying)
								{
									antManager->currentAntGroup.push_back(a);
									a->isSelected = true;
								}
							}
						}
					}
				}

				curX = curY = oldX = oldY = 0;
			}
			else if (drag->GetActive())
			{
				tempX += 40;
				tempY += 40;

				curX = GetPosGridX(tempX);
				curY = GetPosGridY(tempY);

				if (curX < oldX)
				{
					int tem = curX;
					curX = oldX;
					oldX = tem;
				}
				if (curY < oldY)
				{
					int tem = curY;
					curY = oldY;
					oldY = tem;
				}

				for (int i = oldX; i <= curX; i++)
				{
					for (int j = oldY; j <= curY; j++)
					{
						for (auto& a : antManager->antList)
						{
							if (a->x == i && a->y == j && !a->isCarrying)
							{
								antManager->currentAntGroup.push_back(a);
								a->isSelected = true;
							}
						}
					}
				}
			}


			drag->transform->SetPosition(0.f, 0.f);
			drag->transform->SetScale(0.f, 0.f);
			drag->SetActive(false);
			dragX = dragY = 0;
		}

		if (InputManager::GetKeyDown(VK_RBUTTON))
		{
			int tempX = InputManager::GetMouseX();
			int tempY = InputManager::GetMouseY();
			tempX -= 40;
			tempY -= 40;
			if (tempX >= 0 && tempX <= 1464 && tempY >= 0 && tempY <= 824)
			{
				tempX += 40;
				tempY += 40;

				tempX = GetPosGridX(tempX);
				tempY = GetPosGridY(tempY);

				if (GridManager::grid[tempX][tempY] != Grid::OBSTACLE && !antManager->currentAntGroup.empty())
				{
					SetPing(tempX, tempY);
					for (auto& i : antManager->currentAntGroup)
					{
						i->destX = tempX;
						i->destY = tempY;
						i->ResetDest();
					}
				}
			}
		}

		if (InputManager::GetKeyDown(VK_LBUTTON))
		{
			if (selectedButton->col->Intersected(InputManager::GetMouseVector2()) && selectedButton->GetActive())
			{
				OnClickSelectedButton();
			}
			else if (houseupButton->col->Intersected(InputManager::GetMouseVector2()))
			{
				OnHouseUp();
			}
			else if (antaddButton->col->Intersected(InputManager::GetMouseVector2()))
			{
				OnAntAdd();
			}
		}

	}
	else
	{
		if (tempBush->isSet)
			tempBush = nullptr;
	}

}

void GameManager::ManageAnt()
{
	std::list<Ant*> tempList;
	int cnt[20] = { 0, };
	for (auto& i : antManager->antList)
	{
		if (i->state != ANTHOUSE && !i->isCarrying)
		{
			cnt[i->state]++;
			tempList.push_back(i);
		}
	}
	for (int i = 0; i < 20; i++)
	{
		if (i != ANTHOUSE && i != UI_BUSH && i != UI_WATER)
		{
			if (cnt[i] == selectedStatus->value[i].ant)
			{
				for (auto& a : tempList)
				{
					a->state = ANTHOUSE;
				}
				charStatus->waterValue += selectedStatus->value[i].water;
				charStatus->foodValue += selectedStatus->value[i].food;
				charStatus->woodValue += selectedStatus->value[i].wood;
				charStatus->Notify();
				selectedStatus->SetState(ANTHOUSE);
				selectedStatus->SetActive(false);
			}
		}
	}

	_itow_s<4>(antManager->antList.size(), antNumber, 10);

}

void GameManager::ChangeDay()
{
	_itow_s<4>(DayManager::dayCount, dayNumber, 10);
}

void GameManager::ManageDay()
{
	if (dayManager->dayCount - currentDay == 1 && dayManager->dayCount == 2)
	{
		selectedStatus->SetState(ANTHOUSE);
		selectedStatus->SetActive(false);
		selectedButton->SetActive(false);

		antDieCheck = 0;
		for (auto& i : antManager->antList)
		{
			if (GridManager::grid[i->x][i->y] == Grid::BUSH)
			{
				continue;
			}
			antManager->Destroy(i);
			++antDieCheck;
			if (antHouse->GetLevel() == 1)
			{
				if (antDieCheck >= 4)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 2)
			{
				if (antDieCheck >= 3)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 3)
			{
				if (antDieCheck >= 2)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 4)
			{
				if (antDieCheck >= 1)
				{
					break;
				}
			}
		}

		currentDay = dayManager->dayCount;

		charStatus->waterValue -= 4;
		charStatus->foodValue -= 4;
		charStatus->Notify();

	}
	else if (dayManager->dayCount - currentDay == 1 && dayManager->dayCount == 3)
	{
		selectedStatus->SetState(ANTHOUSE);
		selectedStatus->SetActive(false);
		selectedButton->SetActive(false);

		antDieCheck = 0;
		for (auto& i : antManager->antList)
		{
			if (GridManager::grid[i->x][i->y] == Grid::BUSH)
			{
				continue;
			}
			antManager->Destroy(i);
			++antDieCheck;
			if (antHouse->GetLevel() == 1)
			{
				if (antDieCheck >= 14)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 2)
			{
				if (antDieCheck >= 10)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 3)
			{
				if (antDieCheck >= 7)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 4)
			{
				if (antDieCheck >= 4)
				{
					break;
				}
			}
		}

		currentDay = dayManager->dayCount;

		charStatus->waterValue -= 4;
		charStatus->foodValue -= 4;
		charStatus->Notify();

	}
	else if (dayManager->dayCount - currentDay == 1 && dayManager->dayCount == 4)
	{
		selectedStatus->SetState(ANTHOUSE);
		selectedStatus->SetActive(false);
		selectedButton->SetActive(false);

		antDieCheck = 0;
		for (auto& i : antManager->antList)
		{
			if (GridManager::grid[i->x][i->y] == Grid::BUSH)
			{
				continue;
			}
			antManager->Destroy(i);
			++antDieCheck;
			if (antHouse->GetLevel() == 1)
			{
				if (antDieCheck >= 24)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 2)
			{
				if (antDieCheck >= 17)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 3)
			{
				if (antDieCheck >= 10)
				{
					break;
				}
			}
			else if (antHouse->GetLevel() == 4)
			{
				if (antDieCheck >= 6)
				{
					break;
				}
			}
		}

		currentDay = dayManager->dayCount;

		charStatus->waterValue -= 4;
		charStatus->foodValue -= 4;
		charStatus->Notify();

	}
}

void GameManager::ManageCamera()
{

	if (InputManager::GetKeyPressed('W'))
	{
		cameraPos.y -= cameraSpeed;
	}
	else if (InputManager::GetKeyPressed('S'))
	{
		cameraPos.y += cameraSpeed;
	}
	if (InputManager::GetKeyPressed('A'))
	{
		cameraPos.x -= cameraSpeed;
	}
	else if (InputManager::GetKeyPressed('D'))
	{
		cameraPos.x += cameraSpeed;
	}

	if (cameraPos.x > 2148)
	{
		cameraPos.x = 2148;
	}
	else if (cameraPos.x < -2148)
	{
		cameraPos.x = -2148;
	}

	if (cameraPos.y > 1208)
	{
		cameraPos.y = 1208;
	}
	else if (cameraPos.y < -1208)
	{
		cameraPos.y = -1208;
	}

	mapBackground->transform->SetPosition(Vector2(772.f - cameraPos.x, 452.f - cameraPos.y));
	gridBG->transform->SetPosition(Vector2(772.f - cameraPos.x, 452.f - cameraPos.y));

	antHouse->transform->SetPosition(GetGridPos(antHouse->x, antHouse->y));
	ping->transform->SetPosition(GetGridPos(ping->x, ping->y));
	for (auto& i : antManager->antList)
	{
		i->transform->position += i->curCameraPos - cameraPos;
		i->curCameraPos = cameraPos;
	}
	for (auto& i : antManager->soldierList)
	{
		i->transform->position += i->curCameraPos - cameraPos;
		i->curCameraPos = cameraPos;
	}
	for (auto& i : enemyManager->enemyList)
	{
		i->transform->position += i->curCameraPos - cameraPos;
		i->curCameraPos = cameraPos;
	}
	for (auto& i : objectManager->buildList)
		i->transform->SetPosition(GetGridPos(i->x, i->y));
	for (auto& i : objectManager->bushList)
		i->transform->SetPosition(GetGridPos(i->x, i->y));
	for (auto& i : objectManager->foodList)
		i->transform->SetPosition(GetGridPos(i->x, i->y));
	for (auto& i : objectManager->footPrintList)
		i->transform->SetPosition(GetGridPos(i->x, i->y));
	for (auto& i : objectManager->stoneList)
		i->transform->SetPosition(GetGridPos(i->x, i->y));
	for (auto& i : objectManager->trashList)
		i->transform->SetPosition(GetGridPos(i->x, i->y));
	for (auto& i : objectManager->waterList)
		i->transform->SetPosition(GetGridPos(i->x, i->y));
	

}

void GameManager::SetPing(int x, int y)
{
	ping->SetActive(true);
	ping->x = x;
	ping->y = y;
	ping->transform->SetPosition(GetGridPos(x, y));
	ping->renderer->SetAlpha(1.f);
}

void GameManager::SetSelectedUI(StatusUI state, int x, int y)
{
	selectedStatus->SetActive(true);
	selectedStatus->SetState(state);
	selectedButton->SetActive(true);
	selectedButton->SetState(state, x, y);
}

void GameManager::OnClickSelectedButton()
{
	int x = selectedButton->x;
	int y = selectedButton->y;
	StatusUI state = selectedButton->state;

	int max = INT_MAX;
	std::list<Ant*> moveAntList;

	switch (state)
	{
		case ANTHOUSE:
			break;
		case UI_BUILD_1:
		{
			Build* temp = nullptr;
			for (auto& i : objectManager->buildList)
			{
				if (i->state == 1)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_BUILD_2:
		{
			Build* temp = nullptr;
			for (auto& i : objectManager->buildList)
			{
				if (i->state == 2)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_BUILD_3:
		{
			Build* temp = nullptr;
			for (auto& i : objectManager->buildList)
			{
				if (i->state == 3)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_BUSH:
			break;
		case UI_FOOD_1:
		{
			Food* temp = nullptr;
			for (auto& i : objectManager->foodList)
			{
				if (i->state == 0)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_FOOD_2:
		{
			Food* temp = nullptr;
			for (auto& i : objectManager->foodList)
			{
				if (i->state == 1)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_FOOD_3:
		{
			Food* temp = nullptr;
			for (auto& i : objectManager->foodList)
			{
				if (i->state == 2)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_FOOD_4:
		{
			Food* temp = nullptr;
			for (auto& i : objectManager->foodList)
			{
				if (i->state == 3)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_FOOD_5:
		{
			Food* temp = nullptr;
			for (auto& i : objectManager->foodList)
			{
				if (i->state == 4)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_FOOD_6:
		{
			Food* temp = nullptr;
			for (auto& i : objectManager->foodList)
			{
				if (i->state == 5)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_FOOD_7:
		{
			Food* temp = nullptr;
			for (auto& i : objectManager->foodList)
			{
				if (i->state == 6)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_FOOD_8:
		{
			Food* temp = nullptr;
			for (auto& i : objectManager->foodList)
			{
				if (i->state == 7)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_FOOD_9:
		{
			Food* temp = nullptr;
			for (auto& i : objectManager->foodList)
			{
				if (i->state == 8)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_FOOD_10:
		{
			Food* temp = nullptr;
			for (auto& i : objectManager->foodList)
			{
				if (i->state == 9)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_TRASH_1:
		{
			Trash* temp = nullptr;
			for (auto& i : objectManager->trashList)
			{
				if (i->state == 0)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_TRASH_2:
		{
			Trash* temp = nullptr;
			for (auto& i : objectManager->trashList)
			{
				if (i->state == 1)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_TRASH_3:
		{
			Trash* temp = nullptr;
			for (auto& i : objectManager->trashList)
			{
				if (i->state == 2)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_TRASH_4:
		{
			Trash* temp = nullptr;
			for (auto& i : objectManager->trashList)
			{
				if (i->state == 3)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_TRASH_5:
		{
			Trash* temp = nullptr;
			for (auto& i : objectManager->trashList)
			{
				if (i->state == 4)
				{
					int gab = abs(i->x - x) + abs(i->y - y);
					if (gab < max)
					{
						max = gab;
						temp = i;
					}
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			for (auto& i : moveAntList)
			{
				i->SetCarry(state);
			}
			objectManager->Destroy(temp);
			break;
		}
		case UI_WATER:
		{
			Water* temp = nullptr;
			for (auto& i : objectManager->waterList)
			{
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < max)
				{
					max = gab;
					temp = i;
				}
			}
			for (auto& i : antManager->antList)
			{
				if (i->isCarrying)
					continue;
				int gab = abs(i->x - x) + abs(i->y - y);
				if (gab < 8)
				{
					moveAntList.push_back(i);
					if (moveAntList.size() >= selectedStatus->value[state].ant)
						break;
				}
			}
			if (moveAntList.size() < selectedStatus->value[state].ant)
			{
				noAnt->SetActive(true);
				noAnt->renderer->SetAlpha(1.f);
				moveAntList.clear();
				return;
			}
			temp->isDestroy = true;
			charStatus->waterValue += selectedStatus->value[UI_WATER].water;
			charStatus->Notify();
			selectedStatus->SetState(ANTHOUSE);
			selectedStatus->SetActive(false);
			break;
		}
	}

	selectedButton->SetActive(false);
}

void GameManager::OnHouseUp()
{
	if (charStatus->woodValue >= antHouse->GetLevel() + 2)
	{
		if (antHouse->GetLevel() < 4)
		{
			antHouse->SetLevel(antHouse->GetLevel() + 1);
			charStatus->woodValue -= antHouse->GetLevel() + 2;
			charStatus->Notify();
		}
	}
}

void GameManager::OnAntAdd()
{
	if (charStatus->woodValue >= 1)
	{
		SoldierAnt* a = antManager->PushBackAnt(new SoldierAnt(120, 69));
		charStatus->woodValue -= 1;
		charStatus->Notify();
	}
}



void GameManager::SpriteChange(GameObject* g, const wchar_t* path)
{
	SAFE_DELETE(g->renderer);
	g->renderer = new Renderer(Scene::GetCurrentScene().GetResourceManager().LoadBitmapFromFile(path, 0, 0));
	g->renderer->SetLayer(3);
}
