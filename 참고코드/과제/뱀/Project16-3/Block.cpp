#include "Block.h"


Block::Block()
{
	m_icount = 0;
}

void Block::Init_Heart_Block()
{
	if (Heart != NULL)
	{
		delete[] Heart;
	}
	Heart = new Blocks[HEART_BLOCK_COUNT];
	
	for (int i = 0; i < HEART_BLOCK_COUNT; i++)
	{
		Heart[i].m_ix = NULL;
		Heart[i].m_iy = NULL;
		Heart[i].m_ishape = SHAPE_HEART;
	}

}

void Block::Heart_Block()
{
	int count = 0;
	int trigger = FALSE;
	int complete = FALSE;

	for (int i = 0; i < HEART_BLOCK_COUNT; i++)
	{
		if (Heart[i].m_ix == NULL && Heart[i].m_iy == NULL) // ����ִ°� üũ
		{
			Heart[i].m_iy = (rand() % RANDOM_Y); // 0 ~ 28 �߿� 1 ~ 27 ��
			Heart[i].m_ix = (rand() % RANDOM_X); // 0 ~ 96 �߿� 2 ~ 94 ��
			Heart[i].m_ishape = SHAPE_HEART;
			if ((Heart[i].m_iy >= HEART_WALL_Y_MIN && Heart[i].m_iy <= HEART_WALL_Y_MAX) && (Heart[i].m_ix >= HEART_WALL_X_MIN && Heart[i].m_ix <= HEART_WALL_X_MAX) && (Heart[i].m_ix != 50 && Heart[i].m_iy != 15)) // 50, 15�� ��ó����ġ
			{
				if (Heart[i].m_ix % 2 == 0) // ����üũ
				{
					count = i;
					trigger = TRUE;
					break;
				}
				else
				{
					Heart[i].m_iy = NULL;
					Heart[i].m_ix = NULL;
					i--;
				}
			}
			else
			{
				Heart[i].m_iy = NULL;
				Heart[i].m_ix = NULL;
				i--;
			}
		}
	}


	if (trigger == TRUE)
	{
		for (int i = 0; i < SQUARE_BLOCK_COUNT;)
		{
			if (Heart[count].m_ix == Square[i].m_ix && Heart[count].m_iy == Square[i].m_iy)
			{
				Heart[count].m_iy = NULL;
				Heart[count].m_ix = NULL;
				trigger = FALSE;
				break;
			}
			else
			{
				i++;
			}
			if (i == SQUARE_BLOCK_COUNT - 1)
			{
				trigger = FALSE;
				complete = TRUE;
				break;
			}
		}
	}

	if (complete == TRUE)
	{
		gotoxy(Heart[count].m_ix, Heart[count].m_iy);
		cout << SHAPE_HEART;
		complete = FALSE;
	}


}

bool Block::Count_Square_Block(int x, int y)
{
	for (int i = 0; i < SQUARE_BLOCK_COUNT; i++)
	{
		if (x == Square[i].m_ix && y == Square[i].m_iy)
		{
			return true;
		}
	}
	return false;
}

bool Block::Count_Heart_Block(int x, int y)
{
	for (int i = 0; i < HEART_BLOCK_COUNT; i++)
	{
		if (Heart[i].m_ix == NULL && Heart[i].m_iy == NULL)
		{
			break;
		}
		if (x == Heart[i].m_ix && y == Heart[i].m_iy)
		{
			return true;
		}
	}
	return false;
}

bool Block::Count_Wall_Block(int x, int y)
{
	for (int i = 0; i < WALL_BLOCK_COUNT; i++)
	{
		if (x == Wall[i].m_ix && y == Wall[i].m_iy)
		{
			return true;
		}
	}
	return false;
}

void Block::Square_Block()
{

	if (Square != NULL)
	{
		delete[] Square;
	}
	Square = new Blocks[SQUARE_BLOCK_COUNT];

	int count = 0;


	while (count <= SQUARE_BLOCK_COUNT - 1) // �迭�̴ϱ� -1 ����
	{
		Square[count].m_iy = (rand() % RANDOM_Y);
		Square[count].m_ix = (rand() % RANDOM_X);
		Square[count].m_ishape = SHAPE_SUARE;
		if ((Square[count].m_iy % 1 == 0 && Square[count].m_ix % 2 == 0) && (Heart[count].m_ix != 50 && Heart[count].m_iy != 15)) //���ʿ� �̰��߰������� �ؿ� if�� �ʿ��������?
		{
			if (Square[count].m_ix != Wall[count].m_ix && Square[count].m_iy != Wall[count].m_iy)
			{
				if (Square[count].m_ix != 1 && Square[count].m_ix != 0)
					count++;
			}
		}

	}

	for (int i = 0; i < SQUARE_BLOCK_COUNT; i++)
	{
		gotoxy(Square[i].m_ix, Square[i].m_iy);
		cout << SHAPE_SUARE;
	}
}

void Block::Map_Block_Create(int x, int y)
{
	Wall[m_icount].m_iy = y;
	Wall[m_icount].m_ix = x;
	Wall[m_icount].m_ishape = SHAPE_WALL;
}

void Block::Map_Block_Draw()
{
	for (int i = 0; i < m_icount; i++)
	{
		gotoxy(Wall[i].m_ix, Wall[i].m_iy);
		cout << SHAPE_WALL;
	}
}

void Block::Map_Block()
{
	if (Wall != NULL)
	{
		delete[] Wall;
	}
	Wall = new Blocks[WALL_BLOCK_COUNT];

	int x = 0;
	int y = 0;

	while (m_icount < 50) // ���� 50 * 2, ���� 30
	{
		Map_Block_Create(x, y);
		if ((Wall[m_icount].m_iy == 0) && (Wall[m_icount].m_ix <= 98))
		{
			m_icount++;
			x += 2;
		}
	}

	y = 29, x = 0; // �ؿ� ���� �׸���

	while (m_icount < 100)
	{
		Map_Block_Create(x, y);
		if ((Wall[m_icount].m_iy == 29) && (Wall[m_icount].m_ix <= 98))
		{
			m_icount++;
			x += 2;
		}
	}

	y = 0, x = 0; // ���� ���� �׸���

	while (m_icount < 129)
	{
		Map_Block_Create(x, y);
		if ((Wall[m_icount].m_iy <= 29) && (Wall[m_icount].m_ix == 0))
		{
			m_icount++;
			y++;
		}
	}

	y = 0, x = 98; // ������ ���� �׸���

	while (m_icount < WALL_BLOCK_COUNT)
	{
		Map_Block_Create(x, y);
		if ((Wall[m_icount].m_iy <= 29) && (Wall[m_icount].m_ix == 98))
		{
			m_icount++;
			y++;
		}
	}
}

Block::~Block()
{
	if (Heart != NULL)
	{
		delete[] Heart;
		Heart = NULL; // �ҽ�.cpp�� Excute.Init(); ȣ���� ������ ����ȴ�
	}

	if (Square != NULL)
	{
		delete[] Square; // �����Ҵ�����
		Square = NULL;
	}

	if (Wall != NULL)
	{
		delete[] Wall;
		Wall = NULL;
	}
}
