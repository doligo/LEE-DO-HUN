#include "Card.h"

Card::Card()
{

}

void Card::Init(HDC hdc, HINSTANCE hinst, int id)
{
	// main 에서 객체화 시킨것을 20개 만든다
	MemDC = CreateCompatibleDC(hdc);
	m_MyCard = (HBITMAP)LoadBitmap(hinst, MAKEINTRESOURCE(id));
	m_OldCard = (HBITMAP)SelectObject(MemDC, m_MyCard);

	BITMAP Bitmap_info;
	GetObject(m_MyCard, sizeof(Bitmap_info), &Bitmap_info);

	m_size.cx = Bitmap_info.bmWidth;
	m_size.cy = Bitmap_info.bmHeight;
}

void Card::Draw(HDC hdc, int x, int y, int SpX, int SpY)
{

	StretchBlt(hdc, x, y, m_size.cx * SpX, m_size.cy * SpY, MemDC, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
}

Card::~Card()
{
	SelectObject(MemDC, m_OldCard);
	DeleteObject(m_MyCard);
	DeleteDC(MemDC);
}