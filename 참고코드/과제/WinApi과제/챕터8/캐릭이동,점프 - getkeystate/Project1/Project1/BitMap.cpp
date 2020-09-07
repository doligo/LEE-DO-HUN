#include "BitMap.h"

BitMap::BitMap()
{
}

void BitMap::Init(HWND hWnd, HDC hdc, HINSTANCE hInst, int id)
{
	hdc = GetDC(hWnd);

	g_playerDC = CreateCompatibleDC(hdc);
	g_btPlayer = (HBITMAP)LoadImage(NULL, "image.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	g_btOldPlayer = (HBITMAP)SelectObject(g_playerDC, g_btPlayer);

	g_backDC = CreateCompatibleDC(hdc);
	g_btBack = (HBITMAP)LoadImage(NULL, "back.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	g_btOldBack = (HBITMAP)SelectObject(g_backDC, g_btBack);

	GetObject(g_btPlayer, sizeof(g_mapInfo), &g_mapInfo);

	g_size.cx = g_mapInfo.bmWidth;
	g_size.cy = g_mapInfo.bmHeight;

	ReleaseDC(hWnd, hdc);
}
void BitMap::Draw(HDC hdc, int x, int y)
{
	StretchBlt(hdc, x, y, 1024, 768, g_backDC, 0, 0, 102, 768, SRCCOPY);
	TransparentBlt(hdc, x, y, g_size.cx / 4, g_size.cy / 4, g_playerDC, 0, 0, g_size.cx / 4, g_size.cy / 4, RGB(255, 0, 255));
}

BitMap::~BitMap()
{
	SelectObject(MemDC, m_pBitOld);
	DeleteObject(m_pBitMap);
	DeleteDC(MemDC);
}
