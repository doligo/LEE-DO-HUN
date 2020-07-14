#include "Card_Manager.h"
Card_Manager* Card_Manager::m_pThis = NULL;
void CALLBACK TimeProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

Card_Manager::Card_Manager()
{
	m_count = 0;
	m_score = 0;
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

	card_rand = rand() % 10 + 101;
	animal[0] = card_rand;

	for (int j = 0; j < CARD_MAX - 10; j++) // 카드 섞어서 넣기
	{
		again:
		card_rand = rand() % 10 + 101;

		while (j != 0 && animal[num2] != 0)
		{
			if (animal[num2] == card_rand)
			{
				num2 = 0;
				goto again;
			}
			else
			{
				num2++;
			}
		}

		if (j != 0)
		animal[j] = card_rand;

		num2 = 0;

		while (overlap_trigger == FALSE)
		{
			overlap_check = rand() % 20;
			if (m_cd[overlap_check].card_number == NULL)
			{
				m_cd[overlap_check].card_number = animal[j];

				again2:

				overlap_check = rand() % 20;
				if (m_cd[overlap_check].card_number == NULL)
				{
					m_cd[overlap_check].card_number = animal[j];
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

		m_cd[i].Init(hdc, hInst,  _x, _y); // 그외 기본값 설정

		_x += 140;
		num++;

	}
}

void Card_Manager::Draw(HDC hdc)
{
	char buf[256] = {};

	sprintf_s(buf, "Score : %d", m_score);

	TextOut(hdc, 640, 600, buf, lstrlen(buf));

	for (int i = 0; i < CARD_MAX; i++)
	{
		m_cd[i].Draw(hdc);
	}
}

void Card_Manager::Click(HWND hWnd, HDC hdc, int x, int y)
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

	Check_Card(hWnd, hdc);
}

void Card_Manager::Check_Card(HWND hWnd, HDC hdc)
{
	int card[2] = {0 , 1};
	int num = 0;

	for (int i = 0; i < CARD_MAX; i++)
	{
		if (m_cd[i].flip_over == TRUE)
		{
			card[num] = m_cd[i].card_number;
			num++;
		}
	}
	
	if (card[0] == card[1])
	{
		m_score += 100;
	}
	else
	{
		SetTimer(hWnd, 1, 2000, TimeProc);

		KillTimer(hWnd, 1);
	}
}

void CALLBACK TimeProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	cout << "하" << endl;
}

Card_Manager::~Card_Manager()
{

}