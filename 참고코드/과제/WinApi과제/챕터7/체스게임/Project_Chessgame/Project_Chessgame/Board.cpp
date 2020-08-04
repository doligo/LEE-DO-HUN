#include "Board.h"

Board::Board()
{

}

void Board::Board_Init(HDC hdc, HINSTANCE hinst, int x, int y)
{

	MemDC = CreateCompatibleDC(hdc);

	if (board_num == 10)
	hbtmap = (HBITMAP)LoadImage(NULL, "C:\\Users\\A-12\\Desktop\\LEE-DO-HUN\\�����ڵ�\\����\\WinApi����\\é��7\\ü������\\block01.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	else if (board_num == 20)
	hbtmap = (HBITMAP)LoadImage(NULL, "C:\\Users\\A-12\\Desktop\\LEE-DO-HUN\\�����ڵ�\\����\\WinApi����\\é��7\\ü������\\block00.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);

	old_hbtmap = (HBITMAP)SelectObject(MemDC, hbtmap);
	GetObject(hbtmap, sizeof(BITMAP), &btmap);
	m_x = btmap.bmWidth - 50;
	m_y = btmap.bmHeight - 50;

}

void Board::Board_Draw(HDC hdc, int x, int y)
{
	pos_x = x; // ������ ��ġ
	pos_y = y;
	TransparentBlt(hdc, x, y, m_x, m_y, MemDC, 0, 0, m_x, m_y, RGB(255, 0, 255));
}

Board::~Board()
{
	SelectObject(MemDC, old_hbtmap);
	DeleteObject(hbtmap);
	DeleteDC(MemDC);
}