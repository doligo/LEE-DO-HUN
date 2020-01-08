#include "Snake.h"

int Snake::key = 0;
int Snake::direct = 0;

Snake::Snake()
{
	m_pHead = NULL; // ���°͸� �ΰ����� �ʱ�ȭ
}

void Snake::Create_Head()
{
	if (m_pHead != NULL)
	{
		//�� ��ü �����ڵ�
	}

	m_pHead = new Snakes;
	m_pHead->m_MyPositiion.m_ix = 50;// define or enum ����
	m_pHead->m_MyPositiion.m_iy = 15;
	m_pHead->m_LastPositiion.m_ix = 0;
	m_pHead->m_LastPositiion.m_iy = 0;
	m_pHead->m_pNext = NULL;

	Block::gotoxy(m_pHead->m_MyPositiion.m_ix, m_pHead->m_MyPositiion.m_iy);
	cout << SNAKE_HEAD;
}

void Snake::Create_Tail()
{
	m_pTmp = m_pHead; // �����ּҰ��� ������, �����ּҰ��� ���������ϰ�� ���� �ٲ�� ���̹ٲ��.


	while (m_pTmp->m_pNext != NULL)
	{
		m_pTmp = m_pTmp->m_pNext; // null�� �����ϸ� �����κ��̱⶧���� null�� ã������ while��
	}

	m_pTail = new Snakes;
	m_pTail->m_MyPositiion.m_ix = m_pTmp->m_LastPositiion.m_ix;
	m_pTail->m_MyPositiion.m_iy = m_pTmp->m_LastPositiion.m_iy;
	m_pTail->m_LastPositiion.m_ix = 0;
	m_pTail->m_LastPositiion.m_iy = 0;
	m_pTail->m_pNext = NULL;
	m_pTmp->m_pNext = m_pTail;

	Block::gotoxy(m_pTail->m_MyPositiion.m_ix, m_pTail->m_MyPositiion.m_iy);
	cout << SNAKE_TAIL;
}

void Snake::Snake_Tail_Move()
{
	m_pMovetmp2 = m_pHead;

	while (m_pHead->m_pNext != NULL)
	{
		m_pMovetmp = m_pMovetmp2->m_pNext; // ù��° ������ ����

		m_pMovetmp->m_LastPositiion.m_ix = m_pMovetmp->m_MyPositiion.m_ix;
		m_pMovetmp->m_LastPositiion.m_iy = m_pMovetmp->m_MyPositiion.m_iy;

		m_pMovetmp->m_MyPositiion.m_ix = m_pMovetmp2->m_LastPositiion.m_ix;
		m_pMovetmp->m_MyPositiion.m_iy = m_pMovetmp2->m_LastPositiion.m_iy;

		Block::gotoxy(m_pMovetmp->m_LastPositiion.m_ix, m_pMovetmp->m_LastPositiion.m_iy);
		cout << "  ";
		Block::gotoxy(m_pMovetmp->m_MyPositiion.m_ix, m_pMovetmp->m_MyPositiion.m_iy);
		cout << SNAKE_TAIL;

		m_pMovetmp2 = m_pMovetmp2->m_pNext; // �ι�° ����
	}

	//// ù��° ���������� �Ӹ��� ���� �߿����̴µ�
	//// �ι�°�������� ����� ���������ʾ� ��� �ڵ带 ¥�� �������� �߾ȵ˴ϴ�
	//// �ڲ� �����ٺ��� �����µ� ����κ��� �ǵ���� �ι�° ����° ������ �� ������� �ñ��մϴ�
}

void Snake::Snake_Direct(int dir)
{
	if (dir == UP)
	{
		m_pHead->m_MyPositiion.m_iy--;
	}
	else if (dir == DOWN)
	{
		m_pHead->m_MyPositiion.m_iy++;
	}
	else if (dir == RIGHT)
	{
		m_pHead->m_MyPositiion.m_ix += 2;
	}
	else if (dir == LEFT)
	{
		m_pHead->m_MyPositiion.m_ix -= 2;
	}
}

void Snake::Snake_Move_Tmp()
{
	m_pHead->m_LastPositiion.m_ix = m_pHead->m_MyPositiion.m_ix;
	m_pHead->m_LastPositiion.m_iy = m_pHead->m_MyPositiion.m_iy;
}

void Snake::Snake_Move()
{
	Sleep(300);
	Snake_Move_Tmp();

	if (_kbhit())
	{
		direct = _getch();
	}

	if (direct == UP)
	{
		if (key != DOWN)
		{
			Snake_Direct(UP);
			key = direct;
		}
		else
		{
			Snake_Direct(DOWN);
		}
	}
	else if (direct == DOWN)
	{
		if (key != UP)
		{
			Snake_Direct(DOWN);
			key = direct;
		}
		else
		{
			Snake_Direct(UP);
		}
	}
	else if (direct == RIGHT)
	{
		if (key != LEFT)
		{
			Snake_Direct(RIGHT);
			key = direct;
		}
		else
		{
			Snake_Direct(LEFT);
		}

	}
	else if (direct == LEFT)
	{
		if (key != RIGHT)
		{
			Snake_Direct(LEFT);
			key = direct;
		}
		else
		{
			Snake_Direct(RIGHT);
		}
	}

	Snake_Show();

	if (m_pHead->m_pNext != NULL)
	{
		Snake_Tail_Move();
	}
}

void Snake::Snake_Show()
{
	Block::gotoxy(m_pHead->m_LastPositiion.m_ix, m_pHead->m_LastPositiion.m_iy); // �� ��ġ����
	cout << "  ";
	Block::gotoxy(m_pHead->m_MyPositiion.m_ix, m_pHead->m_MyPositiion.m_iy);
	cout << SNAKE_HEAD;
}

Snake::~Snake()
{
}
