#include "Card_Manager.h"
Card_Manager* Card_Manager::m_pThis = NULL;

Card_Manager::Card_Manager()
{
	m_count = 0;
	m_animal[20] = {};
}

void Card_Manager::Init(HDC hdc, HINSTANCE hInst, int SpX, int SpY)
{
	int num = 0;
	int _x = 20;
	int _y = 20;
	int card_rand = 0;
	int trigger = 0;

	srand((unsigned)time(NULL));

	m_cd = new Card[CARD_MAX];

	for (int i = 0; i < CARD_MAX; i++)
	{
		if (num == 10)
		{
			_x = 20;
			_y += 250;
		}

		card_rand = rand() % 10 + 101;

		trigger = Init_Card_Rand(i, card_rand);
		if (trigger == TRUE)
		{
			i--;
			_x -= 140;
			num--;
		}
		else
		m_cd[i].Init(hdc, hInst, card_rand, _x, _y);

		_x += 140;
		num++;

	}
}

int Card_Manager::Init_Card_Rand(int n, int num)
{
	int count = 0;

	for (int i = 0; i < CARD_MAX; i++)
	{
		if (count == 2)
			return TRUE;
		if (m_animal[i] == num)
			count++;
	}

	return 0;
	m_animal[n] = num;
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