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
	BUILD_1,	//������
	BUILD_2,	//��������
	BUILD_3,	//��������(����)
	BUSH,		//Ǯ
	FOOD_1,		//�Ļ�����
	FOOD_2,		//���̽�ũ��
	FOOD_3,		//���� �ν�����
	FOOD_4,		//����
	FOOD_5,		//�߲�ġ
	FOOD_6,		//���
	FOOD_7,		//����
	FOOD_8,		//�����
	FOOD_9,		//�ػ���
	FOOD_10,	//�޶ѱ�
	TRASH_1,	//��������
	TRASH_2,	//������
	TRASH_3,	//����
	TRASH_4,	//����ũ
	TRASH_5,	//���ö�
	WATER,		//�����
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

	static Grid grid[X_SIZE][Y_SIZE]; //grid[x][y] == ��ǥ(x, y)

	Node map[X_SIZE][Y_SIZE];
	std::vector<Node> openList;
	bool closeList[X_SIZE][Y_SIZE];

	std::vector<Node> SetDest(int curX, int curY, int destX, int destY);
	std::vector<Node> MakePath(int destX, int destY);
	int FindHeuristic(int x, int y, int destX, int destY);
};

