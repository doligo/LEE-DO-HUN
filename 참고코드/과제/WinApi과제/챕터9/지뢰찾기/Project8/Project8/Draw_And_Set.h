#include <Windows.h>
#include <iostream>
#pragma once

#define BITMAP_MAX 14
#define BITMAP_SIZE_MAX 13

#define BEGINNER 100
#define INTERMEDIATE 200
#define ADVANCE 300

class Draw_And_Set
{
private:
	BITMAP B_Info;

	HDC MemDC[BITMAP_MAX]; //// 리소스 저장할곳
	HBITMAP	m_BitMap[BITMAP_MAX];
	HBITMAP	m_Old_BitMap[BITMAP_MAX];
	SIZE m_size[BITMAP_SIZE_MAX];

	int m_p_width;
	int m_p_height;
	int m_p_mine;
public:
	Draw_And_Set();

	int difficulty;

	void Init_BitMap(HWND hWnd);
	void Init_Game();
	void Draw_Game_Screen(HDC hdc);

	~Draw_And_Set();
};

