#include "stdafx.h"
#include "GridManager.h"

Grid GridManager::grid[X_SIZE][Y_SIZE] = { Grid::EMPTY, };

GridManager::GridManager()
{

}

GridManager::~GridManager()
{

}

std::vector<Node> GridManager::SetDest(int curX, int curY, int _destX, int _destY)
{
	openList.clear();
	int destX = _destX;
	int destY = _destY;

	std::vector<Node> empty;
	if (grid[destX][destY] != Grid::EMPTY && grid[destX][destY] != Grid::WATER && grid[destX][destY] != Grid::BUSH)
	{
		return empty;
	}
	if (curX == destX && curY == destY)
	{
		return empty;
	}

	for (int x = 0; x < X_SIZE; x++)
	{
		for (int y = 0; y < Y_SIZE; y++)
		{
			map[x][y].f = INT_MAX;
			map[x][y].g = INT_MAX;
			map[x][y].h = INT_MAX;
			map[x][y].pX = -1;
			map[x][y].pY = -1;
			map[x][y].x = x;
			map[x][y].y = y;

			closeList[x][y] = false;
		}
	}

	int x = curX;
	int y = curY;
	map[x][y].f = 0;
	map[x][y].g = 0;
	map[x][y].h = 0;
	map[x][y].pX = x;
	map[x][y].pY = y;

	openList.emplace_back(map[x][y]);
	bool destinationFound = false;

	while (!openList.empty() && openList.size() < X_SIZE * Y_SIZE)
	{
		Node node;
		do
		{
			int temp = INT_MAX;
			std::vector<Node>::iterator itNode;
			for (std::vector<Node>::iterator it = openList.begin(); it != openList.end(); it++)
			{
				Node n = *it;
				if (n.f < temp) {
					temp = n.f;
					itNode = it;
				}
			}
			node = *itNode;
			openList.erase(itNode);
		} while (node.x < 0 && node.x >= X_SIZE && node.y < 0 && node.y >= Y_SIZE && (grid[node.x][node.y] != Grid::EMPTY && grid[node.x][node.y] != Grid::WATER && grid[node.x][node.y] != Grid::BUSH));

		x = node.x;
		y = node.y;
		closeList[x][y] = true;

		for (int newX = -1; newX <= 1; newX++)
		{
			for (int newY = -1; newY <= 1; newY++)
			{
				int gNew, hNew, fNew;
				int gScale;
				if (newX == 0 || newY == 0)
					gScale = 10;
				else
					gScale = 14;
				if (x + newX >= 0 && x + newX < X_SIZE && y + newY >= 0 && y + newY < Y_SIZE && (grid[x + newX][y + newY] == Grid::EMPTY || grid[x + newX][y + newY] == Grid::WATER || grid[x + newX][y + newY] == Grid::BUSH))
				{
					if (x + newX == destX && y + newY == destY)
					{
						map[x + newX][y + newY].pX = x;
						map[x + newX][y + newY].pY = y;
						destinationFound = true;
						return MakePath(destX, destY);
					}
					else if (closeList[x + newX][y + newY] == false)
					{
						gNew = node.g + gScale;
						hNew = FindHeuristic(x + newX, y + newY, destX, destY);
						fNew = gNew + hNew;
						if (map[x + newX][y + newY].f == INT_MAX || map[x + newX][y + newY].f > fNew)
						{
							map[x + newX][y + newY].f = fNew;
							map[x + newX][y + newY].g = gNew;
							map[x + newX][y + newY].h = hNew;
							map[x + newX][y + newY].pX = x;
							map[x + newX][y + newY].pY = y;
							openList.emplace_back(map[x + newX][y + newY]);
						}
					}
				}
			}
		}
	}
	if (destinationFound == false) {
		return empty;
	}
}

std::vector<Node> GridManager::MakePath(int destX, int destY)
{
	int x = destX;
	int y = destY;
	std::vector<Node> path;
	std::vector<Node> realPath;

	while (!(map[x][y].pX == x && map[x][y].pY == y) && map[x][y].x != -1 && map[x][y].y != -1)
	{
		path.push_back(map[x][y]);
		int tempX = map[x][y].pX;
		int tempY = map[x][y].pY;
		x = tempX;
		y = tempY;
	}

	for (int i = path.size() - 1; i >= 0; i--)
	{
		realPath.push_back(path.back());
		path.pop_back();
	}

	return realPath;
}

int GridManager::FindHeuristic(int x, int y, int destX, int destY)
{
	int value = 0;

	value += abs(x - destX) * 10;
	value += abs(y - destY) * 10;

	return value;
}