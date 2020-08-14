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

	m_pr = new Player[2];
	m_pr[0].m_player_num = 0; // 백
	m_pr[1].m_player_num = 1; // 흑
	
	for (int i = 0; i < 2; i++)
		m_pr[i].Init_Player(hdc, m_pr[i].m_player_num);

	Set_All_Pawn_Pos();
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


	for (int i = 0; i < 2; i++)
		m_pr[i].Player_Pieces_Draw(hdc);

}

void Game_System::Click(HDC hdc, int x, int y)
{
	for (int i = 0; i < 2; i++)
	{
		m_pr[i].Move_Check(hdc, x, y);
		All_Pawn_Pos(i); // 이동했을때 좌표저장
		m_pr[i].Click_Check(hdc, i, x, y);
		Pawn_Check(i);
		if (i == 0)
		{
			if (m_pr[0].my_turn == FALSE) // 턴 바꾸는곳 고치기**
				m_pr[1].my_turn = TRUE;
		}
		else if (i == 1)
		{
			if (m_pr[1].my_turn == FALSE)
				m_pr[0].my_turn = TRUE;
		}

	}
}

void Game_System::Set_All_Pawn_Pos()
{
	int num_x = 0;

	for (int i = 0; i < 16; i++)
	{
		m_All_Pawn[i].status = ALIVE;
		if (i < 8)
			m_All_Pawn[i].player_num = 0;
		else
			m_All_Pawn[i].player_num = 1;

		if (i == 0)
		{
			m_All_Pawn[i].x = 0;
			m_All_Pawn[i].y = 450;
			m_All_Pawn[i].rt = { 0, 450, 75, 525 };
		}
		else if (i < 8)
		{
			num_x += 75;
			m_All_Pawn[i].x += num_x;
			m_All_Pawn[i].y = 450;
			m_All_Pawn[i].rt = { num_x, 450, num_x + 75, 525 };
		}
		else if (i == 8)
		{
			num_x = 0;
			m_All_Pawn[i].x = 0;
			m_All_Pawn[i].y = 75;
			m_All_Pawn[i].rt = { 0, 75, 75, 150 };
		}
		else if (i < 16)
		{
			num_x += 75;
			m_All_Pawn[i].x += num_x;
			m_All_Pawn[i].y = 75;
			m_All_Pawn[i].rt = { num_x, 75, num_x + 75, 150 };
		}

	}
}

void Game_System::All_Pawn_Pos(int player_num)
{
	if (m_pr[player_num].tmp_rt.x != NULL)
	{
		if (player_num == 0)
		{
			m_All_Pawn[m_pr[player_num].clicked_object_num].x = m_pr[player_num].tmp_rt.x;
			m_All_Pawn[m_pr[player_num].clicked_object_num].y = m_pr[player_num].tmp_rt.y;
			m_All_Pawn[m_pr[player_num].clicked_object_num].rt = m_pr[player_num].tmp_rt.rt;
		}
		else if (player_num == 1)
		{
			m_All_Pawn[m_pr[player_num].clicked_object_num + 8].x = m_pr[player_num].tmp_rt.x;
			m_All_Pawn[m_pr[player_num].clicked_object_num + 8].y = m_pr[player_num].tmp_rt.y;
			m_All_Pawn[m_pr[player_num].clicked_object_num + 8].rt = m_pr[player_num].tmp_rt.rt;
		}

	}
}

void Game_System::Pawn_Check(int num)
{
	if (m_pr[num].m_player_num == 0 && m_pr[num].clicked_object_num != NULL)
	{
		for (int i = 0; i < 16; i++)
		{
			if (m_All_Pawn[i].rt.top == m_All_Pawn[m_pr[num].clicked_object_num].rt.top - 75 && m_All_Pawn[i].rt.left == m_All_Pawn[m_pr[num].clicked_object_num].rt.left)
			{
				m_pr[num].pawn_front = TRUE;
				m_pr[num].someting = TRUE;
			}
			if (m_All_Pawn[i].player_num == 1 && m_All_Pawn[i].rt.top == m_All_Pawn[m_pr[num].clicked_object_num].rt.top - 75 && m_All_Pawn[i].rt.left == m_All_Pawn[m_pr[num].clicked_object_num].rt.left - 75)
			{
				m_pr[num].pawn_diagonal1 = TRUE;
				m_pr[num].someting = TRUE;
			}
			if (m_All_Pawn[i].player_num == 1 && m_All_Pawn[i].rt.top == m_All_Pawn[m_pr[num].clicked_object_num].rt.top - 75 && m_All_Pawn[i].rt.left == m_All_Pawn[m_pr[num].clicked_object_num].rt.left + 75)
			{
				m_pr[num].pawn_diagonal2 = TRUE;
				m_pr[num].someting = TRUE;
			}
		}

	}
	else if (m_pr[num].m_player_num == 1 && m_pr[num].clicked_object_num != NULL)
	{
		for (int i = 0; i < 16; i++)
		{
			if (m_All_Pawn[i].rt.top == m_All_Pawn[m_pr[num].clicked_object_num + 8].rt.top + 75 && m_All_Pawn[i].rt.left == m_All_Pawn[m_pr[num].clicked_object_num + 8].rt.left)
			{
				m_pr[num].pawn_front = TRUE;
				m_pr[num].someting = TRUE;
			}
			if (m_All_Pawn[i].player_num == 0 && m_All_Pawn[i].rt.top == m_All_Pawn[m_pr[num].clicked_object_num + 8].rt.top + 75 && m_All_Pawn[i].rt.left == m_All_Pawn[m_pr[num].clicked_object_num + 8].rt.left - 75)
			{
				m_pr[num].pawn_diagonal1 = TRUE;
				m_pr[num].someting = TRUE;
			}
			if (m_All_Pawn[i].player_num == 0 && m_All_Pawn[i].rt.top == m_All_Pawn[m_pr[num].clicked_object_num + 8].rt.top + 75 && m_All_Pawn[i].rt.left == m_All_Pawn[m_pr[num].clicked_object_num + 8].rt.left + 75)
			{
				m_pr[num].pawn_diagonal2 = TRUE;
				m_pr[num].someting = TRUE;
			}
		}
	}

}

Game_System::~Game_System()
{

}