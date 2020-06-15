#pragma once
#include "Control.h"

#define MINE 101
#define CHARACTER 111
#define Y 0
#define X 1

#define MINE_COUNT 5
#define MAP_WIDTH 12
#define MAP_HEIGHT 12


class Map : virtual public Control
{
private:
	vector<vector<int>> m_mine_map;
	int character[2];
	int mine[MINE_COUNT][2]; // 마인위치저장
	int LastObjectIndex;
public:
	Map();

	void Init_Map();
	void Map_Draw();

	void Move();
	void Check_Mine();

	~Map();
};

