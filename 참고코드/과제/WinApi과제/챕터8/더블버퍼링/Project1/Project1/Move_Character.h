#include <windows.h>
#include <iostream>
#pragma once

class Move_Character
{
private:
	HDC MemDC[3];
	HBITMAP	m_BitMap[3];
	HBITMAP	m_Old_BitMap[3];
	BITMAP B_Info;
	SIZE	m_size;
public:
	Move_Character();
	int x;
	int y;
	int jump_y;
	int jump_y_2;
	int jump_x;

	int pre_direct;
	int direct;
	int pose;

	void Init(HWND hWnd, HINSTANCE hInst);
	void Draw(HDC hdc);
	void Jump(int degree);
	void Move_X(int x);
	void Move_Y(int y);
	void Key_Up();
	void Key_Down();
	void Key_Left();
	void Key_Right();

	int Double_Check;
	int Jump_Degree;
	int Jump_Trigger;

	~Move_Character();
};

