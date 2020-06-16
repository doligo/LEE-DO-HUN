#include "Map.h"

Map::Map()
{
	LastObjectIndex = NULL;
}

void Map::Init_Map()
{
	int count = 0;
	int r_height, r_width = 0;

	m_mine_map.assign(MAP_HEIGHT, vector<int>(MAP_WIDTH, 0));
	m_mine_map2.assign(MAP_HEIGHT, vector<int>(MAP_WIDTH, 0)); // ����, �׳ɺ�, ���ں� �����Ұ� �Ҵ�
	m_mine_map[0][0] = CHARACTER; // ĳ���� ó�� �׷�����
	character[Y] = 0; // ĳ���� �ʱ���ġ ����
	character[X] = 0;

	srand((unsigned)time(NULL));

	while (count != MINE_COUNT) // ���νɱ�
	{
		r_height = (rand() % MAP_HEIGHT);
		r_width = (rand() % MAP_WIDTH);
		if (r_width != 1 && r_width % 2 == 0)
		{
			if (m_mine_map2[r_height][r_width] == MINE || m_mine_map[r_height][r_width] == CHARACTER)
			{
				continue;
			}
			else
			{
				m_mine_map2[r_height][r_width] = MINE;
				mine[count][Y] = r_height;
				mine[count][X] = r_width;
				count++;
			}
		}

	}

}

void Map::Map_Draw()
{
	vector<vector<int>>::iterator iter_y;
	vector<int>::iterator iter_x;
	int i = 0;

	for (iter_y = m_mine_map.begin(); iter_y != m_mine_map.end(); iter_y++)
	{
		for (iter_x = (*iter_y).begin(); iter_x != (*iter_y).end(); iter_x++)
		{
			if ((*iter_x) == CHARACTER)
				cout << "��";
			else
				cout << "��";
		}
		cout << endl;
	}

	for (iter_y = m_mine_map2.begin(); iter_y != m_mine_map2.end(); iter_y++)
	{
		for (iter_x = (*iter_y).begin(); iter_x != (*iter_y).end(); iter_x++)
		{
			if ((*iter_x) == MINE)
			{
				gotoxy(mine[i][X], mine[i][Y]);
				cout << "��";
				i++;
			}
			else if ((*iter_x) == NOTING)
				cout << "��";
		}
	}
}
void Map::Move()
{
	char ch;
	ch = _getch();

	system("cls");

	m_mine_map[character[Y]][character[X]] = LastObjectIndex;

	switch (ch)
	{
	case LEFT:
		if (character[X] != 0)
		character[X]--;
		break;
	case RIGHT:
		if (character[X] != 11)
		character[X]++;
		break;
	case UP:
		if (character[Y] != 0)
		character[Y]--;
		break;
	case DOWN:
		if (character[Y] != 11)
		character[Y]++;
		break;
	case ENTER:
		Check_Mine();
		break;
	}
	m_mine_map[character[Y]][character[X]] = CHARACTER;
}

void Map::Check_Mine()
{
	for (int i = 0; i < MINE_COUNT; i++)
	{
		if (character[Y] == mine[i][Y] && character[X] == mine[i][X])
		{
			cout << "�����Դϴ�";
			_getch();
			break;
		}
	}

	Spread(character[Y], character[X], 0);
}

void Map::Spread(int y, int x, int what)
{
	if (m_mine_map[y][x] == NULL)
	{
		m_mine_map[y][x] = NOTING;
	}
}

Map::~Map()
{

}