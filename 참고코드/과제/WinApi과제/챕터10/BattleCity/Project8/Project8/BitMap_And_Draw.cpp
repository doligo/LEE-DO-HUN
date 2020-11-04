#include "BitMap_And_Draw.h"

BitMap_And_Draw::BitMap_And_Draw()
{

}

void BitMap_And_Draw::Init_Bitmap(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);

	Entire_DC = CreateCompatibleDC(hdc); // 검은배경
	m_BitMap[0] = CreateCompatibleBitmap(hdc, 1200, 700);
	m_Old_BitMap[0] = (HBITMAP)SelectObject(Entire_DC, m_BitMap[0]);

	for (int i = 0; i < BITMAP_MAX; i++)
	{
		MemDC[i] = CreateCompatibleDC(Entire_DC);
		m_BitMap[i] = (HBITMAP)LoadImage(NULL, m_bitmap[i],
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		m_Old_BitMap[i] = (HBITMAP)SelectObject(MemDC[i], m_BitMap[i]);

		GetObject(m_BitMap[i], sizeof(B_Info), &B_Info);
		m_size[i].cx = B_Info.bmWidth;
		m_size[i].cy = B_Info.bmHeight;
	}
}

BitMap_And_Draw::~BitMap_And_Draw()
{

}