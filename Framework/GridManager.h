#pragma once
#include "GameObject.h"

#define X_SIZE 240
#define Y_SIZE 135
#define GRID_SIZE 24

enum Grid
{
	EMPTY = 0,
	OBSTACLE,
	HOUSE,
	BUILD_1,	//나뭇잎
	BUILD_2,	//나뭇가지
	BUILD_3,	//건축자재(나무)
	BUSH,		//풀
	FOOD_1,		//식빵조각
	FOOD_2,		//아이스크림
	FOOD_3,		//과자 부스러기
	FOOD_4,		//피자
	FOOD_5,		//닭꼬치
	FOOD_6,		//당근
	FOOD_7,		//팝콘
	FOOD_8,		//물고기
	FOOD_9,		//솜사탕
	FOOD_10,	//메뚜기
	TRASH_1,	//휴지조각
	TRASH_2,	//유리병
	TRASH_3,	//깡통
	TRASH_4,	//마스크
	WATER,		//물방울
};

typedef struct _Node
{
	int x, y;
	int g, h, f; //g + h = f
	int pX, pY;
} Node;

class GridManager :
	public GameObject
{
public:
	GridManager();
	~GridManager();

	static Grid grid[X_SIZE][Y_SIZE]; //grid[x][y] == 좌표(x, y)

	Node map[X_SIZE][Y_SIZE];
	std::vector<Node> openList;
	bool closeList[X_SIZE][Y_SIZE];

	std::vector<Node> SetDest(int curX, int curY, int destX, int destY);
	std::vector<Node> MakePath(int destX, int destY);
	int FindHeuristic(int x, int y, int destX, int destY);
};

