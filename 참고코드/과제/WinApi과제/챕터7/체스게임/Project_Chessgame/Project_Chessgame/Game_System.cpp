#include "Game_System.h"

Game_System::Game_System()
{

}

void Game_System::Init_System(HDC hdc, HINSTANCE hinst)
{
	int trigger = FALSE;
	int count = 0;
	int x = 0;
	int y = 0;

	m_bd = new Board[BOARD_MAX];

	for (int i = 0; i < BOARD_MAX; i++)
	{
		if (count == 16)
			count = 0;
		if (trigger == FALSE)
		{
			if (count >= 8)
			{
				m_bd[i].board_num = 20;
				trigger = TRUE;
			}
			else
			{
				m_bd[i].board_num = 10;
				trigger = TRUE;
			}
		}
		else if (trigger == TRUE)
		{
			if (count >= 8)
			{
				m_bd[i].board_num = 10;
				trigger = FALSE;
			}
			else
			{
				m_bd[i].board_num = 20;
				trigger = FALSE;
			}
		}
		count++;
	}

	for (int j = 0; j < BOARD_MAX; j++)
	{
		if (x == 8)
		{
			x = 0;
			y++;
		}
		m_bd[j].Board_Init(hdc, hinst, x, y);
		x++;
	}
}

void Game_System::Draw(HDC hdc)
{
	int x = 0;
	int y = 0;
	int count = 0;

	for (int i = 0; i < BOARD_MAX; i++)
	{
		if (count == 8)
		{
			x = 0;
			y += 75;
			count = 0;
		}
		m_bd[i].Board_Draw(hdc, x, y);
		x += 75;
		count++;
	}
}

Game_System::~Game_System()
{

}