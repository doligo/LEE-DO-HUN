#include <Windows.h>
#include <iostream>
#include <string>
#pragma once

class BackGround
{
private:
	HDC MemDC[5];
	HBITMAP	m_BitMap[5];
	HBITMAP	m_Old_BitMap[5];
	BITMAP B_Info;
	SIZE m_size[4];
public:
	BackGround();

	RECT star_rt[3];
	
	void Init_BackGround(HWND hWnd, HINSTANCE hInst);
	void Draw_TitleScreen(HDC hdc);

	~BackGround();
};

