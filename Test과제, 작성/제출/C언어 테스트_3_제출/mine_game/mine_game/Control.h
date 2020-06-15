#pragma once
#include "Mecro.h"

#define UP 119
#define DOWN 115
#define LEFT 97
#define RIGHT 100
#define ENTER 13

class Control
{
private:
public:
	Control();

	void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	~Control();
};

