#include "BitMap_And_Draw.h"

BitMap_And_Draw::BitMap_And_Draw()
{

}

void BitMap_And_Draw::Init_Bitmap(HWND hWnd)
{
	hdc = GetDC(hWnd);

	Entire_DC = CreateCompatibleDC(hdc); // �������
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
	//// �������ϸ��� �ߺ��� ��� �о�������ϴ°� �߻�, �׳� �ٷ� �����̸��� ���°ɷ� �����ϱ�
}

void BitMap_And_Draw::Draw(int _x, int _y, int _m_size, int dc_num)
{
	TransparentBlt(Entire_DC, _x, _y, m_size[_m_size].cx, m_size[_m_size].cy, MemDC[dc_num], 0, 0, m_size[_m_size].cx, m_size[_m_size].cy, RGB(255, 0, 255));

	BitBlt(hdc, 0, 0, 1200, 700, Entire_DC, 0, 0, SRCCOPY);
}

BitMap_And_Draw::~BitMap_And_Draw()
{

}