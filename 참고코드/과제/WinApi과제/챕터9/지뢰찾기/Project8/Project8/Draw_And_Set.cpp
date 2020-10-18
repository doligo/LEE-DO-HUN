#include "Draw_And_Set.h"

Draw_And_Set::Draw_And_Set()
{

}

void Draw_And_Set::Init_BitMap(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);

	MemDC[0] = CreateCompatibleDC(hdc); // 검은배경
	m_BitMap[0] = CreateCompatibleBitmap(hdc, 1024, 533);
	m_Old_BitMap[0] = (HBITMAP)SelectObject(MemDC[0], m_BitMap[0]);

	/////////////////////////////
}

Draw_And_Set::~Draw_And_Set()
{
	for (int i = 0; i < BITMAP_MAX; i++)
	{
		DeleteObject(m_BitMap[i]);
		DeleteObject(m_Old_BitMap[i]);
		DeleteDC(MemDC[i]);
	}
}