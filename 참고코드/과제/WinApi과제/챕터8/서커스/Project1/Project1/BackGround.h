#include <Windows.h>
#include <iostream>
#include <string>
#pragma once

class BackGround
{
private:
	BITMAP B_Info;

	HDC MemDC[9];
	HBITMAP	m_BitMap[9];
	HBITMAP	m_Old_BitMap[9];
	SIZE m_size[8];

	HDC GameDC[5];
	HBITMAP m_GameBitMap[5];
	HBITMAP m_Old_GameBitMap[5];
	SIZE m_Gamesize[4];

public:
	BackGround();
	
	void Init_BackGround(HWND hWnd, HINSTANCE hInst);
	int Draw_TitleScreen(HDC hdc);
	void Draw_GameScreen(HDC hdc);

	~BackGround();
};

