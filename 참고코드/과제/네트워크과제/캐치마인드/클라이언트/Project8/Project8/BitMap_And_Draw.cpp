#include "BitMap_And_Draw.h"

BitMap_And_Draw::BitMap_And_Draw()
{

}

void BitMap_And_Draw::Init_Bitmap(HWND hWnd)
{
	hdc = GetDC(hWnd);

	Entire_DC = CreateCompatibleDC(hdc); // 검은배경
	m_BitMap[0] = CreateCompatibleBitmap(hdc, 1200, 700);
	m_Old_BitMap[0] = (HBITMAP)SelectObject(Entire_DC, m_BitMap[0]);

	for (int i = 0; i < BITMAP_MAX; i++)
	{
		MemDC[i] = CreateCompatibleDC(Entire_DC);
		m_BitMap[i] = (HBITMAP)LoadImage(NULL, m_bitmap[i], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		m_Old_BitMap[i] = (HBITMAP)SelectObject(MemDC[i], m_BitMap[i]);

		GetObject(m_BitMap[i], sizeof(B_Info), &B_Info);
		m_size[i].cx = B_Info.bmWidth;
		m_size[i].cy = B_Info.bmHeight;
	}
}

void BitMap_And_Draw::Draw(int _x, int _y, int _m_size, int dc_num)
{
	TransparentBlt(Entire_DC, _x, _y, m_size[_m_size].cx, m_size[_m_size].cy, MemDC[dc_num], 0, 0, m_size[_m_size].cx, m_size[_m_size].cy, RGB(255, 0, 255));

	BitBlt(hdc, 0, 0, 1200, 700, Entire_DC, 0, 0, SRCCOPY);
}

void BitMap_And_Draw::Draw_Ready(int _x, int _y, int _m_size, int dc_num)
{
	TransparentBlt(Entire_DC, _x, _y, m_size[_m_size].cx, m_size[_m_size].cy, MemDC[dc_num], 0, 0, m_size[_m_size].cx, m_size[_m_size].cy, RGB(255, 0, 255));
}

void BitMap_And_Draw::Draw_Detail_Ready(int _x, int _y, int _m_size, int dc_num, int x_size, int y_size)
{
	if (_m_size == 10 || _m_size == 8 || _m_size == 7 || _m_size == 11 || _m_size == 22 || _m_size == 14)
		TransparentBlt(Entire_DC, _x, _y, m_size[_m_size].cx + x_size, m_size[_m_size].cy + y_size, MemDC[dc_num], 0, 0, m_size[_m_size].cx, m_size[_m_size].cy, RGB(255, 0, 255));
	else
		TransparentBlt(Entire_DC, _x, _y, m_size[_m_size].cx + x_size, m_size[_m_size].cy + y_size, MemDC[dc_num], 0, 0, m_size[_m_size].cx, m_size[_m_size].cy, RGB(255, 255, 255));
}

void BitMap_And_Draw::Draw_Go()
{
	BitBlt(hdc, 0, 0, 1200, 700, Entire_DC, 0, 0, SRCCOPY);
}

void BitMap_And_Draw::Draw_Black_BackGround()
{
	TransparentBlt(Entire_DC, 0, 0, m_size[Black_BackGround].cx + 1200, m_size[Black_BackGround].cy + 680, MemDC[Black_BackGround], 0, 0, m_size[Black_BackGround].cx, m_size[Black_BackGround].cy, RGB(255, 0, 255));
	BitBlt(hdc, 0, 0, 1200, 700, Entire_DC, 0, 0, SRCCOPY);
}

void BitMap_And_Draw::Draw_Name_WaitRoom(char *name)
{
	RECT rt = { 874, 526, 974, 546 };
	RECT rt2 = { 847, 526, 970, 546 };

	if (strlen(name) <= 5)
		DrawText(Entire_DC, name, -1, &rt, DT_VCENTER | DT_WORDBREAK);
	else
		DrawText(Entire_DC, name, -1, &rt2, DT_VCENTER | DT_WORDBREAK);
}

BitMap_And_Draw::~BitMap_And_Draw()
{

}