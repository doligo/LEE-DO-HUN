#include "Card_Manager.h"
Card_Manager* Card_Manager::m_pThis = NULL;

Card_Manager::Card_Manager()
{
	m_count = 0;
}

void Card_Manager::Init(HDC hdc, HINSTANCE hInst, int SpX, int SpY)
{
	int num = 0;
	int _x = 20;
	int _y = 20;
	int card_rand = 0;
	int trigger = 0;
	int overlap_check = 0;
	int overlap_trigger = FALSE;
	int animal[10] = {};
	int num2 = 0;

	srand((unsigned)time(NULL));

	m_cd = new Card[CARD_MAX];

	for (int o = 0; o < CARD_MAX; o++) // 카드 넘버 초기화
	{
		m_cd[o].card_number = NULL;
	}

	for (int j = 0; j < CARD_MAX - 10; j++)
	{ // 이부분 고치기
		again:
		card_rand = rand() % 10 + 101;
		animal[j] = card_rand;

		while (j != 0 && animal[num2] != 0)
		{
			if (animal[num2] == card_rand)
			{
				goto again;
			}
			else
			{
				num2++;
			}
		}

		num2 = 0;

		while (overlap_trigger == FALSE)
		{
			overlap_check = rand() % 20;
			if (m_cd[overlap_check].card_number == NULL)
			{
				m_cd[overlap_check].card_number = card_rand;

				again2:

				overlap_check = rand() % 20;
				if (m_cd[overlap_check].card_number == NULL)
				{
					m_cd[overlap_check].card_number = card_rand;
					overlap_trigger = TRUE;
				}
				else
				{
					goto again2;
				}
			}
		}
		overlap_trigger = FALSE;
	}



	for (int i = 0; i < CARD_MAX; i++)
	{
		if (num == 10)
		{
			_x = 20;
			_y += 250;
		}

		m_cd[i].Init(hdc, hInst,  _x, _y);

		_x += 140;
		num++;

	}
}

void Card_Manager::Draw(HDC hdc)
{

	for (int i = 0; i < CARD_MAX; i++)
	{
		m_cd[i].Draw(hdc);
	}
}

void Card_Manager::Click(int x, int y)
{
	int flag = 0;

	for (int i = 0; i < CARD_MAX; i++)
	{
		if (m_count == 2)
		{
			break;
		}

		flag = m_cd[i].Click(m_cd[i], x, y);
		//if (flag == TRUE)
			//m_count++;
	}

}

Card_Manager::~Card_Manager()
{

}