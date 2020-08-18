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

	hbtmap = (HBITMAP)LoadImage(NULL, "C:\\Users\\A-12\\Desktop\\LEE-DO-HUN\\참고코드\\과제\\WinApi과제\\챕터7\\체스게임\\block03.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);

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

	clicked_object_num = NULL;
	tmp_rt.x = NULL;
	tmp_rt.y = NULL;
	who_is_moved = NULL;

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
		if (Cp->m_Pawn[i].status == ALIVE)
		Cp->Pieces_Draw(hdc, Cp->m_Pawn[i].x, Cp->m_Pawn[i].y, buf);
	}

	Move_Able_Point(hdc); // 장기 클릭시 이동 범위출력

}

void Player::Move_Able_Point(HDC hdc)
{

	int draw_pawn_path = 0;

	if (select_num == SELECT_PAWN)
	{
		for (int i = 0; i < 8; i++)
		{
			if (clicked_object_num == i)
			{
				if (Cp->m_Pawn[clicked_object_num].first_move == TRUE)
					draw_pawn_path = TRUE;
			}
		}
	}

	// clicked_pos_x와 y에 +20은 꼭넣어야 사각형이 중앙에 그려진다
	//// pawn
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
		if (draw_pawn_path == FALSE && someting == FALSE)
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
		if (draw_pawn_path == FALSE && someting == FALSE)
			TransparentBlt(hdc, clicked_pos_x + 20, clicked_pos_y + 150 + 20, m_x - 90, m_y - 90, MemDC, 0, 0, m_x, m_y, RGB(255, 0, 255));
	}

	//// rook
	else if (select_num == SELECT_ROOK && m_player_num == 0 && my_turn == TRUE)
	{
		for (int i = 0; i < rook_front; i++)
			TransparentBlt(hdc, clicked_pos_x + 20, clicked_pos_y - 75 + 20, m_x - 90, m_y - 90, MemDC, 0, 0, m_x, m_y, RGB(255, 0, 255));
	}
	else if (select_num == SELECT_ROOK && m_player_num == 1 && my_turn == TRUE)
	{

	}

}

int Player::Move_Check(HDC hdc, int x, int y)
{
	// 클릭한곳으로 말을 옮기는 함수
	if (select_num == SELECT_PAWN && m_player_num == 0 && my_turn == TRUE) // 폰
	{
		if (selected_object_rt.left <= x && selected_object_rt.right >= x && selected_object_rt.top - 75 <= y && selected_object_rt.bottom - 75 >= y && pawn_front != TRUE)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top - 75;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left, selected_object_rt.top - 75, selected_object_rt.left + 75, selected_object_rt.top - 75 + 75 };

			tmp_rt.x = selected_object_rt.left;
			tmp_rt.y = selected_object_rt.top - 75;
			tmp_rt.rt = { selected_object_rt.left, selected_object_rt.top - 75, selected_object_rt.left + 75, selected_object_rt.top - 75 + 75 };

			select_num = 0;
			my_turn = FALSE;
			Cp->m_Pawn[clicked_object_num].first_move = TRUE;
			who_is_moved = clicked_object_num;
			return TRUE;
		}
		else if (selected_object_rt.left <= x && selected_object_rt.right >= x && selected_object_rt.top - 150 <= y && selected_object_rt.bottom - 150 >= y && Cp->m_Pawn[clicked_object_num].first_move != TRUE && someting == FALSE)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top - 150;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left, selected_object_rt.top - 150, selected_object_rt.left + 75, selected_object_rt.top - 150 + 75 };

			tmp_rt.x = selected_object_rt.left;
			tmp_rt.y = selected_object_rt.top - 150;
			tmp_rt.rt = { selected_object_rt.left, selected_object_rt.top - 150, selected_object_rt.left + 75, selected_object_rt.top - 150 + 75 };

			select_num = 0;
			my_turn = FALSE;
			Cp->m_Pawn[clicked_object_num].first_move = TRUE;
			who_is_moved = clicked_object_num;
			return TRUE;
		}
		else if (selected_object_rt.left - 75 <= x && selected_object_rt.right - 75 >= x && selected_object_rt.top - 75 <= y && selected_object_rt.bottom - 75 >= y && pawn_diagonal1 == TRUE)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left - 75;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top - 75;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left - 75, selected_object_rt.top - 75, selected_object_rt.left - 75 + 75, selected_object_rt.top - 75 + 75 };

			tmp_rt.x = selected_object_rt.left - 75;
			tmp_rt.y = selected_object_rt.top - 75;
			tmp_rt.rt = { selected_object_rt.left - 75, selected_object_rt.top - 75, selected_object_rt.left - 75 + 75, selected_object_rt.top - 75 + 75 };

			select_num = 0;
			my_turn = FALSE;
			who_is_moved = clicked_object_num;
			return TRUE;
		}
		else if (selected_object_rt.left + 75 <= x && selected_object_rt.right + 75 >= x && selected_object_rt.top - 75 <= y && selected_object_rt.bottom - 75 >= y && pawn_diagonal2 == TRUE)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left + 75;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top - 75;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left + 75, selected_object_rt.top - 75, selected_object_rt.left + 75 + 75, selected_object_rt.top - 75 + 75 };

			tmp_rt.x = selected_object_rt.left + 75;
			tmp_rt.y = selected_object_rt.top - 75;
			tmp_rt.rt = { selected_object_rt.left + 75, selected_object_rt.top - 75, selected_object_rt.left + 75 + 75, selected_object_rt.top - 75 + 75 };

			select_num = 0;
			my_turn = FALSE;
			who_is_moved = clicked_object_num;
			return TRUE;
		}
	}

	else if (select_num == SELECT_PAWN && m_player_num == 1 && my_turn == TRUE) // 폰
	{
		if (selected_object_rt.left <= x && selected_object_rt.right >= x && selected_object_rt.top + 75 <= y && selected_object_rt.bottom + 75 >= y && pawn_front != TRUE)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top + 75;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left, selected_object_rt.top + 75, selected_object_rt.left + 75, selected_object_rt.top + 75 + 75 };

			tmp_rt.x = selected_object_rt.left;
			tmp_rt.y = selected_object_rt.top + 75;
			tmp_rt.rt = { selected_object_rt.left, selected_object_rt.top + 75, selected_object_rt.left + 75, selected_object_rt.top + 75 + 75 };

			select_num = 0;
			my_turn = FALSE;
			Cp->m_Pawn[clicked_object_num].first_move = TRUE;
			who_is_moved = clicked_object_num;
			return TRUE;
		}
		else if (selected_object_rt.left <= x && selected_object_rt.right >= x && selected_object_rt.top + 150 <= y && selected_object_rt.bottom + 150 >= y && Cp->m_Pawn[clicked_object_num].first_move != TRUE && someting == FALSE)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top + 150;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left, selected_object_rt.top + 150, selected_object_rt.left + 75, selected_object_rt.top + 150 + 75 };

			tmp_rt.x = selected_object_rt.left;
			tmp_rt.y = selected_object_rt.top + 150;
			tmp_rt.rt = { selected_object_rt.left, selected_object_rt.top + 150, selected_object_rt.left + 75, selected_object_rt.top + 150 + 75 };

			select_num = 0;
			my_turn = FALSE;
			Cp->m_Pawn[clicked_object_num].first_move = TRUE;
			who_is_moved = clicked_object_num;
			return TRUE;
		}
		else if (selected_object_rt.left - 75 <= x && selected_object_rt.right - 75 >= x && selected_object_rt.top + 75 <= y && selected_object_rt.bottom + 75 >= y && pawn_diagonal1 == TRUE)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left - 75;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top + 75;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left - 75, selected_object_rt.top + 75, selected_object_rt.left - 75 + 75, selected_object_rt.top + 75 + 75 };

			tmp_rt.x = selected_object_rt.left - 75;
			tmp_rt.y = selected_object_rt.top + 75;
			tmp_rt.rt = { selected_object_rt.left - 75, selected_object_rt.top + 75, selected_object_rt.left - 75 + 75, selected_object_rt.top + 75 + 75 };

			select_num = 0;
			my_turn = FALSE;
			who_is_moved = clicked_object_num;
			return TRUE;
		}
		else if (selected_object_rt.left + 75 <= x && selected_object_rt.right + 75 >= x && selected_object_rt.top + 75 <= y && selected_object_rt.bottom + 75 >= y && pawn_diagonal2 == TRUE)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left + 75;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top + 75;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left + 75, selected_object_rt.top + 75, selected_object_rt.left + 75 + 75, selected_object_rt.top + 75 + 75 };

			tmp_rt.x = selected_object_rt.left + 75;
			tmp_rt.y = selected_object_rt.top + 75;
			tmp_rt.rt = { selected_object_rt.left + 75, selected_object_rt.top + 75, selected_object_rt.left + 75 + 75, selected_object_rt.top + 75 + 75 };

			select_num = 0;
			my_turn = FALSE;
			who_is_moved = clicked_object_num;
			return TRUE;
		}
	}

	who_is_moved = -1;
	tmp_rt.x = -1;
	tmp_rt.y = -1;
	return FALSE;
}

void Player::Click_Check(HDC hdc, int player_num, int x, int y)
{
	// 말선택후 이동가능한 경로를 설정하는 함수

	if (my_turn == TRUE)
	{
		for (int i = 0; i < 8; i++)
		{
			if (Cp->m_Pawn[i].rt.left <= x && Cp->m_Pawn[i].rt.right >= x && Cp->m_Pawn[i].rt.top <= y && Cp->m_Pawn[i].rt.bottom >= y && Cp->m_Pawn[i].status == ALIVE) // 클릭한 말이 범위안에 있을때
			{
				// pawn
				select_num = SELECT_PAWN;
				select_what = SELECT_PAWN; // 게임시스템에서 사용하기 위해만듬
				clicked_pos_x = Cp->m_Pawn[i].rt.left;
				clicked_pos_y = Cp->m_Pawn[i].rt.top;
				clicked_object_num = i;
				selected_object_rt = { Cp->m_Pawn[i].rt.left, Cp->m_Pawn[i].rt.top, Cp->m_Pawn[i].rt.right, Cp->m_Pawn[i].rt.bottom };
				break;
			}
			else if (Cp->m_Rook[i].rt.left <= x && Cp->m_Rook[i].rt.right >= x && Cp->m_Rook[i].rt.top <= y && Cp->m_Rook[i].rt.bottom >= y && Cp->m_Rook[i].status == ALIVE)
			{
				// rook
				select_num = SELECT_ROOK;
				select_what = SELECT_ROOK;
				clicked_pos_x = Cp->m_Rook[i].rt.left;
				clicked_pos_y = Cp->m_Rook[i].rt.top;
				clicked_object_num = i;
				selected_object_rt = { Cp->m_Rook[i].rt.left, Cp->m_Rook[i].rt.top, Cp->m_Rook[i].rt.right, Cp->m_Rook[i].rt.bottom };
				break;
			}
			else
			{
				clicked_object_num = -1;
				select_num = 0;
			}
		}
	}
}

void Player::Player_Die_Check(int piece_num, int dead_num)
{
	if (piece_num == 10) // pawn
	{
		Cp->m_Pawn[dead_num].status = DEAD;
	}
}

Player::~Player()
{

}