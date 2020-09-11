#include <Windows.h>
#include <iostream>
#include <string>
#pragma once

class BackGround
{
private:
	HDC MemDC[4];
	HBITMAP	m_BitMap[4];
	HBITMAP	m_Old_BitMap[4];
	BITMAP B_Info;
	SIZE m_size[3];
public:
	BackGround();

	void Init_BackGround(HWND hWnd, HINSTANCE hInst);

	~BackGround();
};

