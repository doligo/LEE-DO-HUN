#include "Mine_Game.h"

Mine_Game::Mine_Game()
{
	m_imypos[2] = {};
	m_imine_max = 0;
	m_width = 10;
	m_height = 10;
	m_ix = 0;
	m_iy = 0;
}

void Mine_Game::Init()
{
	int trigger = FALSE;

	m_imine_max = 7;
	m_iempty_max = m_width * m_height - m_imine_max;
	m_ix = (WIDTH - m_width) * 0.5;
	m_iy = (HEIGHT - m_height) * 0.5;
	m_imypos[X] = m_width * 0.5;
	m_imypos[Y] = m_height * 0.5;

	m_igame_map = new int*[m_height];
	m_igame_map2 = new int*[m_height];

	for (int i = 0; i < m_height; i++)
	{
		m_igame_map[i] = new int[m_width];
		m_igame_map2[i] = new int[m_width];
	}

	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			m_igame_map[i][j] = NULL;
			m_igame_map2[i][j] = WALL;
		}
	}

	for (int i = 0; i < m_imine_max; i++) //// 마인심기
	{
		m_imine[i][X] = rand() % m_width;
		m_imine[i][Y] = rand() % m_height;
		for (int j = 0; j < i; j++)
		{
			if (m_imine[i][X] == m_imine[j][X] && m_imine[i][Y] == m_imine[j][Y])
			{
				trigger = TRUE;
				break;
			}
		}
		if (trigger == TRUE)
		{
			trigger = FALSE;
			i--;
			continue;
		}
	}

	for (int i = 0; i < m_imine_max; i++)
	{
		m_igame_map[m_imine[i][Y]][m_imine[i][X]] = MINE;
	}

	Map_Init(m_width, m_height);
	DrawMap(m_width, m_height, m_ix, m_iy);
	DrawPoint("★", (m_imypos[X] + m_ix) * 2, (m_imypos[Y] + m_iy));
}

void Mine_Game::Map_Init(int width, int height)
{
	int _x, _y;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (m_igame_map[y][x] == MINE)
			{
				for (int k = 0; k < 8; k++)
				{
					if (k == 0)
					{
						if (y == 0)
							continue;
						_y = y - 1;
						_x = x;
					}
					else if (k == 1)
					{
						if (y >= height - 1)
							continue;
						_y = y + 1;
						_x = x;
					}
					else if (k == 2)
					{
						if (y == 0 || x == 0)
							continue;
						_y = y - 1;
						_x = x - 1;
					}
					else if (k == 3)
					{
						if (x == 0)
							continue;
						_y = y;
						_x = x - 1;
					}
					else if (k == 4)
					{
						if (y >= height - 1 || x == 0)
							continue;
						_y = y + 1;
						_x = x - 1;
					}
					else if (k == 5)
					{
						if (y == 0 || x >= width - 1)
							continue;
						_y = y - 1;
						_x = x + 1;
					}
					else if (k == 6)
					{
						if (x >= width - 1)
							continue;
						_y = y;
						_x = x + 1;
					}
					else if (k == 7)
					{
						if (y >= height - 1 || x >= width - 1)
							continue;
						_y = y + 1;
						_x = x + 1;
					}
					if (m_igame_map[_y][_x] == MINE || _x < 0 || _y < 0 || _x >= width || _y >= height)
						continue;
					m_igame_map[_y][_x]++;
				}
			}
		}
	}
}

int Mine_Game::Control(int x, int y)
{
	char ch;
	while (1)
	{
		if (_kbhit())
		{
			ch = _getch();
			if (ch == ENTER)
			{
				return ch;
			}
			if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd')
			{
				DrawPoint(Symbol(m_igame_map2[m_imypos[X]][m_imypos[Y]]), (m_imypos[X] + m_ix) * 2, (m_imypos[Y] + m_iy));
				switch (ch)
				{
				case 'w':
					if (m_imypos[Y] >= x)
						m_imypos[Y]--;
					break;
				case 'a':
					if (m_imypos[X] >= y)
						m_imypos[X]--;
					break;
				case 's':
					if (m_imypos[Y] < m_height - 1)
						m_imypos[Y]++;
					break;
				case 'd':
					if (m_imypos[X] < m_width - 1)
						m_imypos[X]++;
					break;
				}
				DrawPoint("★", (m_imypos[X] + m_ix) * 2, (m_imypos[Y] + m_iy));
			}
		}
	}
}

string Mine_Game::Symbol(int n)
{
	if (n == NULL)
		return "□";
	else if (n == 1)
		return"１";
	else if (n == 2)
		return"２";
	else if (n == 3)
		return"３";
	else if (n == 4)
		return"４";
	else if (n == 5)
		return"５";
	else if (n == 6)
		return"６";
	else if (n == 7)
		return"７";
	else if (n == 8)
		return"８";
	else if (n == MINE)
		return"※";
	else if (n == WALL)
		return"■";
}

void Mine_Game::EmptyCheck(int width, int height, int x, int y)
{
	int Right = FALSE;
	int Left = FALSE;
	int Up = FALSE;
	int Down = FALSE;

	if (m_igame_map2[y][x + 1] != NULL && x + 1 != width) // 오른쪽끝이 아니면서 NULL이 아닐시
	{
		if (m_igame_map[y][x + 1] != NULL)
		{
			Right = TRUE;
			m_igame_map2[y][x + 1] = m_igame_map[y][x + 1];
			DrawPoint(Symbol(m_igame_map2[y][x + 1]), (x + 1 + m_ix) * 2, y + m_ix);
		}
		else
		{
			m_igame_map2[y][x + 1] = NULL;
			DrawPoint("□", (x + 1 + m_ix) * 2, y + m_iy);
			EmptyCheck(width, height, x + 1, y); // 재귀
		}
	}

	if (m_igame_map2[y][x - 1] != NULL && x - 1 != -1) // 왼쪽체크
	{
		if (m_igame_map[y][x - 1] != NULL)
		{
			Left = TRUE;
			m_igame_map2[y][x - 1] = m_igame_map[y][x - 1];
			DrawPoint(Symbol(m_igame_map2[y][x - 1]), (x - 1 + m_ix) * 2, y + m_ix);
		}
		else
		{
			m_igame_map2[y][x - 1] = NULL;
			DrawPoint("□", (x - 1 + m_ix) * 2, y + m_iy);
			EmptyCheck(width, height, x - 1, y); // 재귀
		}
	}
}

bool Mine_Game::Check(int width, int height)
{
	m_igame_map2[m_imypos[Y]][m_imypos[X]] = m_igame_map[m_imypos[Y]][m_imypos[X]];
	DrawPoint(Symbol(m_igame_map2[m_imypos[Y]][m_imypos[X]]), (m_imypos[X] + m_ix) * 2, (m_imypos[Y] + m_iy));
	if (m_igame_map2[m_imypos[Y]][m_imypos[X]] == MINE)
		return false;
	if (m_igame_map2[m_imypos[Y]][m_imypos[X]] == NULL)
	{
		EmptyCheck(width, height, m_imypos[X], m_imypos[X]);
	}
	return true;
}

void Mine_Game::Play()
{
	int select = 0;

	while (1)
	{
		select = Control();
		if (select == ENTER)
		{
			if (Check(m_width, m_height) == false)
			{
				DrawMidText("!게임오버!", WIDTH, HEIGHT*0.5);
				gotoxy(0, HEIGHT + 4);
				_getch();
				return;
			}
		}
	}
}

Mine_Game::~Mine_Game()
{

}