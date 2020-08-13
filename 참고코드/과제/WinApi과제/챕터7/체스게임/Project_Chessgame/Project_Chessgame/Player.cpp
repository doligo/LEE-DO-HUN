#include "Player.h"

Player::Player()
{

}

void Player::Init_Player(HDC hdc, int player_num)
{
	Cp = new chess_pieces;

	Cp->Init_pieces(hdc, player_num);
	Cp->Init_pieces_2(hdc, player_num);

	MemDC = CreateCompatibleDC(hdc);

	hbtmap = (HBITMAP)LoadImage(NULL, "C:\\Users\\L\\Documents\\GitHub\\LEE-DO-HUN\\참고코드\\과제\\WinApi과제\\챕터7\\체스게임\\block03.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);

	old_hbtmap = (HBITMAP)SelectObject(MemDC, hbtmap);
	GetObject(hbtmap, sizeof(BITMAP), &btmap);
	m_x = btmap.bmWidth;
	m_y = btmap.bmHeight;

	if (player_num == 0)
	{
		my_turn = TRUE;
	}
	else if (player_num == 1)
	{
		my_turn = FALSE;
	}


}

void Player::Player_Pieces_Draw(HDC hdc)
{
	char buf[30] = {};

	Cp->Pieces_Draw(hdc, Cp->m_King.x, Cp->m_King.y, "king");
	Cp->Pieces_Draw(hdc, Cp->m_Queen.x, Cp->m_Queen.y, "queen");
	Cp->Pieces_Draw(hdc, Cp->m_Rook[0].x, Cp->m_Rook[0].y, "rook1");
	Cp->Pieces_Draw(hdc, Cp->m_Rook[1].x, Cp->m_Rook[1].y, "rook2");
	Cp->Pieces_Draw(hdc, Cp->m_Bishop[0].x, Cp->m_Bishop[0].y, "bishop1");
	Cp->Pieces_Draw(hdc, Cp->m_Bishop[1].x, Cp->m_Bishop[1].y, "bishop2");
	Cp->Pieces_Draw(hdc, Cp->m_Knight[0].x, Cp->m_Knight[0].y, "knight1");
	Cp->Pieces_Draw(hdc, Cp->m_Knight[1].x, Cp->m_Knight[1].y, "knight2");

	for (int i = 0; i < 8; i++)
	{
		sprintf_s(buf, "pawn%d", i + 1);
		Cp->Pieces_Draw(hdc, Cp->m_Pawn[i].x, Cp->m_Pawn[i].y, buf);
	}

	Move_Able_Point(hdc); // 장기 클릭시 이동 범위출력

}

void Player::Move_Able_Point(HDC hdc)
{

	int draw_pawn_path = 0;

	for (int i = 0; i < 8; i++)
	{
		if (clicked_object_num == i)
		{
			if (Cp->m_Pawn[clicked_object_num].first_move == TRUE)
				draw_pawn_path = TRUE;
		}
	}

	// clicked_pos_x와 y에 +20은 꼭넣어야 사각형이 중앙에 그려진다

	if (select_num == SELECT_PAWN && m_player_num == 0 && my_turn == TRUE)
	{
		if (someting == TRUE)
		{
			if (pawn_diagonal1 == TRUE)
				TransparentBlt(hdc, clicked_pos_x - 75 + 20, clicked_pos_y - 75 + 20, m_x - 90, m_y - 90, MemDC, 0, 0, m_x, m_y, RGB(255, 0, 255));
			if (pawn_diagonal2 == TRUE)
				TransparentBlt(hdc, clicked_pos_x + 75 + 20, clicked_pos_y - 75 + 20, m_x - 90, m_y - 90, MemDC, 0, 0, m_x, m_y, RGB(255, 0, 255));
		}
		if (pawn_front != TRUE)
			TransparentBlt(hdc, clicked_pos_x + 20, clicked_pos_y - 75 + 20, m_x - 90, m_y - 90, MemDC, 0, 0, m_x, m_y, RGB(255, 0, 255));
		if (draw_pawn_path == FALSE)
			TransparentBlt(hdc, clicked_pos_x + 20, clicked_pos_y - 150 + 20, m_x - 90, m_y - 90, MemDC, 0, 0, m_x, m_y, RGB(255, 0, 255));
	}

	else if (select_num == SELECT_PAWN && m_player_num == 1 && my_turn == TRUE)
	{
		if (someting == TRUE)
		{
			if (pawn_diagonal1 == TRUE)
				TransparentBlt(hdc, clicked_pos_x - 75 + 20, clicked_pos_y + 75 + 20, m_x - 90, m_y - 90, MemDC, 0, 0, m_x, m_y, RGB(255, 0, 255));
			if (pawn_diagonal2 == TRUE)
				TransparentBlt(hdc, clicked_pos_x + 75 + 20, clicked_pos_y + 75 + 20, m_x - 90, m_y - 90, MemDC, 0, 0, m_x, m_y, RGB(255, 0, 255));
		}
		if (pawn_front != TRUE)
			TransparentBlt(hdc, clicked_pos_x + 20, clicked_pos_y + 75 + 20, m_x - 90, m_y - 90, MemDC, 0, 0, m_x, m_y, RGB(255, 0, 255));
		if (draw_pawn_path == FALSE)
			TransparentBlt(hdc, clicked_pos_x + 20, clicked_pos_y + 150 + 20, m_x - 90, m_y - 90, MemDC, 0, 0, m_x, m_y, RGB(255, 0, 255));

	}

}

void Player::Move_Check(HDC hdc, int x, int y)
{
	// 클릭한곳으로 말을 옮기는 함수
	if (select_num == SELECT_PAWN && m_player_num == 0 && my_turn == TRUE) // 폰
	{
		if (selected_object_rt.left <= x && selected_object_rt.right >= x && selected_object_rt.top - 75 <= y && selected_object_rt.bottom - 75 >= y && pawn_front != TRUE)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top - 75;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left, selected_object_rt.top - 75, selected_object_rt.left + 75, selected_object_rt.top - 75 + 75 };
			m_All_Pawn[clicked_object_num].rt = { selected_object_rt.left, selected_object_rt.top - 75, selected_object_rt.left + 75, selected_object_rt.top - 75 + 75 };
			select_num = 0;
			my_turn = FALSE;
			Cp->m_Pawn[clicked_object_num].first_move = TRUE;
		}
		else if (selected_object_rt.left <= x && selected_object_rt.right >= x && selected_object_rt.top - 150 <= y && selected_object_rt.bottom - 150 >= y && Cp->m_Pawn[clicked_object_num].first_move != TRUE)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top - 150;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left, selected_object_rt.top - 150, selected_object_rt.left + 75, selected_object_rt.top - 150 + 75 };
			m_All_Pawn[clicked_object_num].rt = { selected_object_rt.left, selected_object_rt.top - 150, selected_object_rt.left + 75, selected_object_rt.top - 150 + 75 };
			select_num = 0;
			my_turn = FALSE;
			Cp->m_Pawn[clicked_object_num].first_move = TRUE;
		}
		else if (selected_object_rt.left - 75 <= x && selected_object_rt.right - 75 >= x && selected_object_rt.top - 75 <= y && selected_object_rt.bottom - 75 >= y && pawn_diagonal1 == TRUE)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left - 75;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top - 75;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left - 75, selected_object_rt.top - 75, selected_object_rt.left - 75 + 75, selected_object_rt.top - 75 + 75 };
			m_All_Pawn[clicked_object_num].rt = { selected_object_rt.left - 75, selected_object_rt.top - 75, selected_object_rt.left - 75 + 75, selected_object_rt.top - 75 + 75 };
			select_num = 0;
			my_turn = FALSE;
		}
		else if (selected_object_rt.left + 75 <= x && selected_object_rt.right + 75 >= x && selected_object_rt.top - 75 <= y && selected_object_rt.bottom - 75 >= y && pawn_diagonal2 == TRUE)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left + 75;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top - 75;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left + 75, selected_object_rt.top - 75, selected_object_rt.left + 75 + 75, selected_object_rt.top - 75 + 75 };
			m_All_Pawn[clicked_object_num].rt = { selected_object_rt.left + 75, selected_object_rt.top - 75, selected_object_rt.left + 75 + 75, selected_object_rt.top - 75 + 75 };
			select_num = 0;
			my_turn = FALSE;
		}
	}

	else if (select_num == SELECT_PAWN && m_player_num == 1 && my_turn == TRUE) // 폰
	{
		if (selected_object_rt.left <= x && selected_object_rt.right >= x && selected_object_rt.top + 75 <= y && selected_object_rt.bottom + 75 >= y && pawn_front != TRUE)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top + 75;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left, selected_object_rt.top + 75, selected_object_rt.left + 75, selected_object_rt.top + 75 + 75 };
			m_All_Pawn[clicked_object_num + 8].rt = { selected_object_rt.left, selected_object_rt.top + 75, selected_object_rt.left + 75, selected_object_rt.top + 75 + 75 };
			select_num = 0;
			my_turn = FALSE;
			Cp->m_Pawn[clicked_object_num].first_move = TRUE;
		}
		else if (selected_object_rt.left <= x && selected_object_rt.right >= x && selected_object_rt.top + 150 <= y && selected_object_rt.bottom + 150 >= y && Cp->m_Pawn[clicked_object_num].first_move != TRUE)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top + 150;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left, selected_object_rt.top + 150, selected_object_rt.left + 75, selected_object_rt.top + 150 + 75 };
			m_All_Pawn[clicked_object_num + 8].rt = { selected_object_rt.left, selected_object_rt.top + 150, selected_object_rt.left + 75, selected_object_rt.top + 150 + 75 };
			select_num = 0;
			my_turn = FALSE;
			Cp->m_Pawn[clicked_object_num].first_move = TRUE;
		}
		else if (selected_object_rt.left - 75 <= x && selected_object_rt.right >= x - 75 && selected_object_rt.top + 75 <= y && selected_object_rt.bottom + 75 >= y && pawn_diagonal1 == TRUE)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left - 75;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top + 75;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left - 75, selected_object_rt.top + 75, selected_object_rt.left - 75 + 75, selected_object_rt.top + 75 + 75 };
			m_All_Pawn[clicked_object_num + 8].rt = { selected_object_rt.left - 75, selected_object_rt.top + 75, selected_object_rt.left - 75 + 75, selected_object_rt.top + 75 + 75 };
			select_num = 0;
			my_turn = FALSE;
		}
		else if (selected_object_rt.left + 75 <= x && selected_object_rt.right >= x + 75 && selected_object_rt.top + 75 <= y && selected_object_rt.bottom + 75 >= y && pawn_diagonal2 == TRUE)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left + 75;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top + 75;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left + 75, selected_object_rt.top + 75, selected_object_rt.left + 75 + 75, selected_object_rt.top + 75 + 75 };
			m_All_Pawn[clicked_object_num + 8].rt = { selected_object_rt.left + 75, selected_object_rt.top + 75, selected_object_rt.left + 75 + 75, selected_object_rt.top + 75 + 75 };
			select_num = 0;
			my_turn = FALSE;
		}
	}

	someting = FALSE;
	pawn_front = FALSE;
	pawn_diagonal1 = FALSE;
	pawn_diagonal2 = FALSE;
}

void Player::Click_Check(HDC hdc, int player_num, int x, int y)
{
	// 이동경로 그리는 함수
	if (my_turn == TRUE)
	{
		for (int i = 0; i < 8; i++) // pawn
		{
			if (Cp->m_Pawn[i].rt.left <= x && Cp->m_Pawn[i].rt.right >= x && Cp->m_Pawn[i].rt.top <= y && Cp->m_Pawn[i].rt.bottom >= y) // 클릭한 말이 범위안에 있을때
			{
				Pawn_Check(i);

				select_num = SELECT_PAWN;
				clicked_pos_x = Cp->m_Pawn[i].rt.left;
				clicked_pos_y = Cp->m_Pawn[i].rt.top;
				clicked_object_num = i;
				selected_object_rt = { Cp->m_Pawn[i].rt.left, Cp->m_Pawn[i].rt.top, Cp->m_Pawn[i].rt.right, Cp->m_Pawn[i].rt.bottom };
				break;
			}
			else
				select_num = 0;
		}
	}
}

void Player::Pawn_Check(int num) 
{
	if (m_player_num == 0)
	{
		for (int i = 0; i < 16; i++)
		{
			if (m_All_Pawn[i].rt.top == Cp->m_Pawn[num].rt.top - 75 && m_All_Pawn[i].rt.left == Cp->m_Pawn[num].rt.left)
			{
				pawn_front = TRUE;
				someting = TRUE;
			}
			if (m_All_Pawn[i].player_num == 1 && m_All_Pawn[i].rt.top == Cp->m_Pawn[num].rt.top - 75 && m_All_Pawn[i].rt.left == Cp->m_Pawn[num].rt.left - 75)
			{
				pawn_diagonal1 = TRUE;
				someting = TRUE;
			}
			if (m_All_Pawn[i].player_num == 1 && m_All_Pawn[i].rt.top == Cp->m_Pawn[num].rt.top - 75 && m_All_Pawn[i].rt.left == Cp->m_Pawn[num].rt.left + 75)
			{
				pawn_diagonal2 = TRUE;
				someting = TRUE;
			}
		}

	}
	else if (m_player_num == 1)
	{
		for (int i = 0; i < 16; i++)
		{
			if (m_All_Pawn[i].rt.top == Cp->m_Pawn[num].rt.top + 75 && m_All_Pawn[i].rt.left == Cp->m_Pawn[num].rt.left)
			{
				pawn_front = TRUE;
				someting = TRUE;
			}
			if (m_All_Pawn[i].player_num == 0 && m_All_Pawn[i].rt.top == Cp->m_Pawn[num].rt.top + 75 && m_All_Pawn[i].rt.left == Cp->m_Pawn[num].rt.left - 75)
			{
				pawn_diagonal1 = TRUE;
				someting = TRUE;
			}
			if (m_All_Pawn[i].player_num == 0 && m_All_Pawn[i].rt.top == Cp->m_Pawn[num].rt.top + 75 && m_All_Pawn[i].rt.left == Cp->m_Pawn[num].rt.left + 75)
			{
				pawn_diagonal2 = TRUE;
				someting = TRUE;
			}
		}
	}

}

Player::~Player()
{

}