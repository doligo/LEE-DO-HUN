#include "Board.h"
#pragma once

class Game_System
{
private:
	Board *m_bd;
	Player *m_pr;
public:
	Game_System();

	void Init_System(HDC hdc, HINSTANCE hinst);
	void Draw(HDC hdc);
	void Click(HWND hWnd, HDC hdc, int x , int y);

	~Game_System();
};

