#include "chess_pieces.h"
#pragma once

#define SELECT_PAWN 8
#define SELECT_ROOK 9

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
	int someting;
	RECT_AND_STATUS tmp_rt;
	int who_is_moved;
	int select_what;

	//// pawn 이동규칙변수
	int pawn_front;
	int pawn_diagonal1;
	int pawn_diagonal2;
	//// rook 이동규칙변수
	int rook_front;
	int rook_back;
	int rook_left;
	int rook_right;

	void Init_Player(HDC hdc, int player_num);
	void Player_Pieces_Draw(HDC hdc);
	void Move_Able_Point(HDC hdc);
	void Click_Check(HDC hdc, int player_num, int x, int y);
	int Move_Check(HDC hdc, int x, int y);
	void Player_Die_Check(int piece_num, int dead_num);

	~Player();
};

