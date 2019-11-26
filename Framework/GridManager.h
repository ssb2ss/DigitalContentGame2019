#pragma once
#include "GameObject.h"

#define X_SIZE 61
#define Y_SIZE 34
#define GRID_SIZE 24

enum Grid
{
	EMPTY = 0,
	OBSTACLE,
	HOUSE,
	BUILD_1,
	BUILD_2,
	BUSH,
	FOOD_1,
	FOOD_2,
	FOOD_3,
	FOOD_4,
	FOOD_5,
	TRASH_1,
	TRASH_2,
	TRASH_3,
	WATER
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

	static Grid grid[X_SIZE][Y_SIZE]; //grid[x][y] == ÁÂÇ¥(x, y)

	Node map[X_SIZE][Y_SIZE];
	std::vector<Node> openList;
	bool closeList[X_SIZE][Y_SIZE];

	std::vector<Node> SetDest(int curX, int curY, int destX, int destY);
	std::vector<Node> MakePath(int destX, int destY);
	int FindHeuristic(int x, int y, int destX, int destY);
};

