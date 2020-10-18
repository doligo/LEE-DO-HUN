#include <Windows.h>
#include <iostream>
#pragma once

#define BITMAP_MAX 14
#define BITMAP_SIZE_MAX 13

class Draw_And_Set
{
private:
	BITMAP B_Info;

	HDC MemDC[BITMAP_MAX]; //// 리소스 저장할곳
	HBITMAP	m_BitMap[BITMAP_MAX];
	HBITMAP	m_Old_BitMap[BITMAP_MAX];
	SIZE m_size[BITMAP_SIZE_MAX];
public:
	Draw_And_Set();

	void Init_BitMap(HWND hWnd);

	~Draw_And_Set();
};

