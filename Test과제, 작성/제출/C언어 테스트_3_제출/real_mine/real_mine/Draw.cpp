#include "Draw.h"

Draw::Draw()
{
}

void Draw::DrawPoint(string str, int x, int y)
{
	gotoxy(x, y);
	cout << str;
}

void Draw::ErasePoint(int x, int y)
{
	gotoxy(x, y);
	cout << "  ";
}

void Draw::DrawMidText(string str, int width, int y)
{
	gotoxy((width - str.length()*0.5), y);
	cout << str;
}

void Draw::DrawMap(int width, int height, int x, int y)
{
	for (int _y = y; _y < y + height; _y++)
	{
		for (int _x = x; _x < x + width; _x++)
		{
			gotoxy(_x * 2, _y);
			cout << "бс";
		}
	}
}

Draw::~Draw()
{
}