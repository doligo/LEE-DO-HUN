#include "Card_Manager.h"
Card_Manager* Card_Manager::m_pThis = NULL;

Card_Manager::Card_Manager()
{
	m_count = 0;
}

void Card_Manager::Init(HDC hdc, HINSTANCE hInst, int SpX, int SpY)
{
	int num = 0;
	int card_num = 0;
	int _x = 20;
	int _y = 20;

	m_cd = new Card[CARD_MAX];

	for (int i = 0; i < CARD_MAX; i++)
	{
		if (num == 10)
		{
			_x = 20;
			_y += 250;
			card_num = 0;
		}

		m_cd[i].Init(hdc, hInst, IDB_BITMAP1 + card_num, _x, _y);

		_x += 140;
		card_num++;
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
		if (flag == TRUE)
			m_count++;
	}

}

Card_Manager::~Card_Manager()
{

}