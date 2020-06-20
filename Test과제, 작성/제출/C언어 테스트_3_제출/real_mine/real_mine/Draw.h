#pragma once
#include "Mecro.h"

class Draw
{
public:
	Draw();

	void DrawPoint(string str, int x, int y);
	void ErasePoint(int x, int y);
	void DrawMidText(string str, int width, int y);
	void DrawMap(int width, int height, int x, int y);

	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	~Draw();
};

