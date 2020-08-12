#include "chess_pieces.h"
#pragma once

#define SELECT_PAWN 8

class Player
{
private:
	chess_pieces *Cp;
	int select_num;
	HDC MemDC;
	HBITMAP hbtmap, old_hbtmap;
	BITMAP btmap;
public:
	Player();

	int m_x;
	int m_y;
	int clicked_pos_x;
	int clicked_pos_y;
	int clicked_object_num;
	RECT selected_object_rt;
	int m_player_num;
	int my_turn;

	void Init_Player(HDC hdc, int player_num);
	void Player_Pieces_Draw(HDC hdc);
	void Move_Able_Point(HDC hdc);
	void Click_Check(HDC hdc, int player_num, int x, int y);
	void Move_Check(HDC hdc, int x, int y);
	int Pawn_Check(int num);

	~Player();
};

