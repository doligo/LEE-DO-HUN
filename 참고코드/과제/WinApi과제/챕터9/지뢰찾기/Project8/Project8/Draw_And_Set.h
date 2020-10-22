#include <Windows.h>
#include <iostream>
#pragma once

#define BITMAP_MAX 14
#define BITMAP_SIZE_MAX 13

#define BEGINNER 100
#define INTERMEDIATE 200
#define ADVANCE 300

#define BEGINNER_BLOCK 99
#define INTERMEDIATE_BLOCK 256
#define ADVANCE_BLOCK 480
#define BLOCK_MAX 480

struct BLOCK
{
	int mine;
	int click;
	int flag;
	int count_mine;
	RECT block_pos;
};

class Draw_And_Set
{
private:
	BITMAP B_Info;

	HDC MemDC[BITMAP_MAX]; //// 리소스 저장할곳
	HBITMAP	m_BitMap[BITMAP_MAX];
	HBITMAP	m_Old_BitMap[BITMAP_MAX];
	SIZE m_size[BITMAP_SIZE_MAX];

	int playing;
	int m_p_width;
	int m_p_height;
	int m_p_mine;
	BLOCK map_block[BLOCK_MAX];
public:
	Draw_And_Set();

	int difficulty;

	void Init_BitMap(HWND hWnd);
	void Init_Game();
	void Draw_Game_Screen(HDC hdc);
	void Left_Click(int x, int y);
	void Right_Click(int x, int y);

	~Draw_And_Set();
};

