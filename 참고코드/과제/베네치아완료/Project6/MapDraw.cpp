#include "MapDraw.h"


MapDraw::MapDraw()
{

}

void MapDraw::EraseWord(int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << " ";
	}
}

void MapDraw::DrawBlind(int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "=";
	}
}

void MapDraw::ErasePoint(int x, int y)
{
	gotoxy(x * 2, y);
	cout << "  ";
	gotoxy(-1, -1);
	return;
}
void MapDraw::DrawPoint(string str, int x, int y)
{
	gotoxy(x * 2, y);
	cout << str;
	gotoxy(-1, -1);
	return;
}

void MapDraw::DrawMidText(string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}
void MapDraw::TextDraw(string str, int x, int y)
{
	gotoxy(x, y);
	cout << str;
}

void MapDraw::HeartDraw(int x, int y)
{
	gotoxy(x, y);
	cout << "♥";
}

void MapDraw::EraseHeart(int x, int y)
{
	gotoxy(x, y);
	cout << "                       ";
}

int MapDraw::XY_Save(int n, int st_x, int st_y, int x, int y)
{
	LB_x[n] = st_x + x;
	LB_y[n] = st_y + y;
	n++;

	return n;
}

void MapDraw::LittleBox(int Start_x, int Start_y, int Width, int Height)
{
	int num = 0;

	if (Start_x > Width)
		Start_x -= Width;
	for (int y = 0; y < Height; y++)
	{
		gotoxy(Start_x, Start_y + y);
		num = XY_Save(num, Start_x, Start_y, 0, y);
		if (y == 0)
		{
			cout << "┌";
			for (int x = 1; x < Width - 1; x++)
			{
				cout << "─";
				num = XY_Save(num, Start_x, Start_y, x, y);
			}
			num = XY_Save(num, Start_x, Start_y, Width - 1, y);
			cout << "┐";
		}
		else if (y == Height - 1)
		{
			cout << "└";
			for (int x = 1; x < Width - 1; x++)
			{
				cout << "─";
				num = XY_Save(num, Start_x, Start_y, x, y);
			}
			LB_x[num] = Start_x + Width - 1;
			LB_y[num] = Start_y + y; // 마지막이라 num++;는 뺀다, 필요없는 코드였음
			cout << "┘";
		}
		else
		{
			cout << "│";
			for (int x = 1; x < Width - 1; x++)
			{
				cout << "  ";
				num = XY_Save(num, Start_x, Start_y, x, y);
			}
			num = XY_Save(num, Start_x, Start_y, Width - 1, y);
			cout << "│";
		}
	}
	return;
}

void MapDraw::BoxErase(int Width, int Height)
{
	for (int y = 1; y < Height - 1; y++)
	{
		gotoxy(2, y);
		for (int x = 1; x < Width - 1; x++)
			cout << "  ";
	}
}

void MapDraw::BoxDraw(int Start_x, int Start_y, int Width, int Height)
{
	char buf[256];
	sprintf_s(buf, "mode con: cols=%d lines=%d ", WIDTH * 2, HEIGHT + 5);
	system(buf);

	if (Start_x > Width)
		Start_x -= Width;
	for (int y = 0; y < Height; y++)
	{
		gotoxy(Start_x, Start_y + y);
		if (y == 0)
		{
			cout << "┌";
			for (int x = 1; x < Width - 1; x++)
				cout << "─";
			cout << "┐";
		}
		else if (y == Height - 1)
		{
			cout << "└";
			for (int x = 1; x < Width - 1; x++)
				cout << "─";
			cout << "┘";
		}
		else
		{
			cout << "│";
			for (int x = 1; x < Width - 1; x++)
				cout << "  ";
			cout << "│";
		}
	}
	return;
}

int MapDraw::MenuSelectCursor(int MenuLen, int AddCol, int x, int y)
{
	int Select = 1;
	RED
		DrawPoint("▶", x, y);
	ORIGINAL
		while (1)
		{
			switch (_getch())
			{
			case UP:
				if (Select - 1 >= 1)
				{
					ErasePoint(x, y);
					y -= AddCol;
					Select--;
				}
				break;
			case DOWN:
				if (Select + 1 <= MenuLen)
				{
					ErasePoint(x, y);
					y += AddCol;
					Select++;
				}
				break;
			case ENTER:
				return Select;
			}
			RED
				DrawPoint("▶", x, y);
			ORIGINAL
		}
}
MapDraw::~MapDraw()
{
}
