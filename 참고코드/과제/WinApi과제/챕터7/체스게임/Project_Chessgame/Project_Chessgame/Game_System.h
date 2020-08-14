#include "Board.h"
#include "chess_pieces.h"
#pragma once


class Game_System
{
private:
	Board *m_bd;
	Player *m_pr;
public:
	Game_System();

	RECT_AND_STATUS m_All_Pawn[16];

	void Init_System(HDC hdc, HINSTANCE hinst);
	void Draw(HDC hdc);
	void Click(HDC hdc, int x , int y);
	void Set_All_Pawn_Pos();
	void All_Pawn_Pos(int player_num);
	void Pawn_Check(int num);

	~Game_System();
};

