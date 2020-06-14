#include "Map.h"

Map::Map()
{

}

void Map::Init_Map()
{
	int count = 0;
	int r_height, r_width = 0;

	m_mine_map.assign(MAP_HEIGHT, vector<int>(MAP_WIDTH, 0));
	m_mine_map[0][0] = CHARACTER; // 캐릭터 처음 그려질곳

	srand((unsigned)time(NULL));

	while (count != MINE_COUNT)
	{
		r_height = (rand() % MAP_HEIGHT);
		r_width = (rand() % MAP_WIDTH);
		if (m_mine_map[r_height][r_width] == MINE || m_mine_map[r_height][r_width] == CHARACTER)
		{
			continue;
		}
		else
		{
			m_mine_map[r_height][r_width] = MINE;
			count++;
		}
	}

}

void Map::Map_Draw_First()
{
	vector<vector<int>>::iterator iter_y;
	vector<int>::iterator iter_x;


	for (iter_y = m_mine_map.begin(); iter_y != m_mine_map.end(); iter_y++)
	{
		for (iter_x = (*iter_y).begin(); iter_x != (*iter_y).end(); iter_x++)
		{
			if ((*iter_x) == CHARACTER)
				cout << "■";
			else
				cout << "□";
		}
		cout << endl;
	}

}

void Map::Map_Draw_Second()
{
	vector<vector<int>>::iterator iter_y;
	vector<int>::iterator iter_x;


	for (iter_y = m_mine_map.begin(); iter_y != m_mine_map.end(); iter_y++)
	{
		for (iter_x = (*iter_y).begin(); iter_x != (*iter_y).end(); iter_x++)
		{
			if ((*iter_x) == FALSE)
				cout << "□";
			else if ((*iter_x) == MINE)
				cout << "※";
		}
		cout << endl;
	}

}

void Map::Move()
{
	char ch;
	ch = _getch();
	switch (ch)
	{
	case LEFT:
		break;
	}
}

Map::~Map()
{

}