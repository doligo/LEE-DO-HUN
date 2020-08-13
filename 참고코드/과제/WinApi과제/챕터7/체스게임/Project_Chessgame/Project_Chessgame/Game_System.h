#include "Board.h"
#include "All_pieces_pos.h"
#pragma once

class Game_System
{
private:
	Board *m_bd;
	Player *m_pr;
	All_pieces_pos *m_all_p_pos;
public:
	Game_System();

	void Init_System(HDC hdc, HINSTANCE hinst);
	void Draw(HDC hdc);
	void Click(HDC hdc, int x , int y);


	~Game_System();
};

