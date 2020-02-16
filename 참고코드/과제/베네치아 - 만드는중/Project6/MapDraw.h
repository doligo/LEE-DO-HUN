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
	void HeartDraw(int x, int y);// 하트 그리기
	void EraseHeart(int x, int y);// 하트 삭제
	void LittleBox(int Start_x, int Start_y, int Width, int Height);// 작은박스
	int MenuSelectCursor(int MenuLen, int AddCol, int x, int y);
	int XY_Save(int n, int st_x, int st_y, int x, int y);
	int LB_x[SAVE_XY_MAX]; // LittleBox 입력창 좌표저장, 사용안해도됌
	int LB_y[SAVE_XY_MAX];
	void EraseWord(int n);
	void DrawBlind(int n);
	MapDraw();
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~MapDraw();
};