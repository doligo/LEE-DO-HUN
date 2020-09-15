#include <Windows.h>
#include <iostream>
#include <string>
#pragma once

class BackGround
{
private:
	HDC MemDC[9];
	HBITMAP	m_BitMap[9];
	HBITMAP	m_Old_BitMap[9];
	BITMAP B_Info;
	SIZE m_size[8];
public:
	BackGround();
	
	void Init_BackGround(HWND hWnd, HINSTANCE hInst);
	void Draw_TitleScreen(HDC hdc);

	~BackGround();
};

