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

	hbtmap = (HBITMAP)LoadImage(NULL, "\\Users\\L\\Documents\\GitHub\\LEE-DO-HUN\\참고코드\\과제\\WinApi과제\\챕터7\\체스게임\\block03.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);

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
{// clicked_pos_x와 y에 +20은 꼭넣어야 사각형이 중앙에 그려진다
	if (select_num == SELECT_PAWN && m_player_num == 0 && my_turn == TRUE)
	{
		TransparentBlt(hdc, clicked_pos_x + 20, clicked_pos_y - 75 + 20, m_x - 90, m_y - 90, MemDC, 0, 0, m_x, m_y, RGB(255, 0, 255));
		TransparentBlt(hdc, clicked_pos_x + 20, clicked_pos_y - 150 + 20, m_x - 90, m_y - 90, MemDC, 0, 0, m_x, m_y, RGB(255, 0, 255));
	}

	else if (select_num == SELECT_PAWN && m_player_num == 1 && my_turn == TRUE)
	{
		TransparentBlt(hdc, clicked_pos_x + 20, clicked_pos_y + 75 + 20, m_x - 90, m_y - 90, MemDC, 0, 0, m_x, m_y, RGB(255, 0, 255));
		TransparentBlt(hdc, clicked_pos_x + 20, clicked_pos_y + 150 + 20, m_x - 90, m_y - 90, MemDC, 0, 0, m_x, m_y, RGB(255, 0, 255));\
	}
}

void Player::Move_Check(HDC hdc, int x, int y)
{
	if (select_num == SELECT_PAWN && m_player_num == 0 && my_turn == TRUE)
	{
		if (selected_object_rt.left <= x && selected_object_rt.right >= x && selected_object_rt.top - 75 <= y && selected_object_rt.bottom - 75 >= y)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top - 75;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left, selected_object_rt.top - 75, selected_object_rt.left + 75, selected_object_rt.top - 75 + 75 };
			select_num = 0;
			my_turn = FALSE;
		}
	}

	else if (select_num == SELECT_PAWN && m_player_num == 1 && my_turn == TRUE)
	{
		if (selected_object_rt.left <= x && selected_object_rt.right >= x && selected_object_rt.top + 75 <= y && selected_object_rt.bottom + 75 >= y)
		{
			Cp->m_Pawn[clicked_object_num].x = selected_object_rt.left;
			Cp->m_Pawn[clicked_object_num].y = selected_object_rt.top + 75;
			Cp->m_Pawn[clicked_object_num].rt = { selected_object_rt.left, selected_object_rt.top + 75, selected_object_rt.left + 75, selected_object_rt.top + 75 + 75 };
			select_num = 0;
		}
	}

}

void Player::Click_Check(HDC hdc, int player_num, int x, int y)
{

	for (int i = 0; i < 8; i++) // pawn
	{
		if (Cp->m_Pawn[i].rt.left <= x && Cp->m_Pawn[i].rt.right >= x && Cp->m_Pawn[i].rt.top <= y && Cp->m_Pawn[i].rt.bottom >= y)
		{
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

Player::~Player()
{

}