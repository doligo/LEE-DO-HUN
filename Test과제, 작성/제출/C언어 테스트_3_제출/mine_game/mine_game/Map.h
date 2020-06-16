#pragma once
#include "Control.h"

#define MINE 101
#define WALL 201
#define CHARACTER 111
#define Y 0
#define X 1

#define WALL_MAX 144
#define MINE_COUNT 5
#define MAP_WIDTH 12
#define MAP_HEIGHT 12


class Map : virtual public Control
{
private:
	vector<vector<int>> m_mine_map;
	vector<vector<int>> m_mine_map2; // ����, ���ں�, �׳ɺ� ��ġ��¿�
	int wall[WALL_MAX][2];
	int wall_count;
	int mine[MINE_COUNT][2]; // ������ġ����
	int character[2];
	int LastObjectIndex;
public:
	Map();

	void Init_Map();
	void Map_Draw();

	void Move();
	void Check_Mine();
	int Spread(int y, int x);

	~Map();
};

