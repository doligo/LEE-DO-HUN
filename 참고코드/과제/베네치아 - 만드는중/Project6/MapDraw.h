#pragma once
#include"Mecro.h"

#define UP 'w'
#define DOWN 's'
#define ENTER 13
#define SAVE_XY_MAX 95


class MapDraw
{
public:
	void BoxDraw(int Start_x, int Start_y, int Width, int Height);
	void BoxErase(int Width, int Height);
	void DrawPoint(string str, int x, int y);
	void DrawMidText(string str, int x, int y);
	void TextDraw(string str, int x, int y);
	void ErasePoint(int x, int y);
	void HeartDraw(int x, int y);// ��Ʈ �׸���
	void EraseHeart(int x, int y);// ��Ʈ ����
	void LittleBox(int Start_x, int Start_y, int Width, int Height);// �����ڽ�
	int MenuSelectCursor(int MenuLen, int AddCol, int x, int y);
	int XY_Save(int n, int st_x, int st_y, int x, int y);
	int LB_x[SAVE_XY_MAX]; // LittleBox �Է�â ��ǥ����, �����ص���
	int LB_y[SAVE_XY_MAX];
	void EraseWord(int n);
	MapDraw();
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~MapDraw();
};