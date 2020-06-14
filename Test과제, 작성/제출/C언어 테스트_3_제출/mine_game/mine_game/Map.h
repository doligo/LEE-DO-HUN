#pragma once
#include "Mecro.h"

#define MINE 101
#define CHARACTER 111

#define MINE_COUNT 5
#define MAP_WIDTH 12
#define MAP_HEIGHT 12

class Map
{
private:
	vector<vector<int>> m_mine_map;
public:
	Map();

	void Init_Map();
	void Map_Draw_First(); // ���ڰ� �־ ������ �ʱ����ȭ��
	void Map_Draw_Second();

	~Map();
};

