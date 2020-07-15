#include "Card.h"

Card::Card()
{

}

void Card::Init(HDC hdc, HINSTANCE hinst, int x, int y, int SpX, int SpY)
{
	//// 검은카드 설정
	MemDC_Black = CreateCompatibleDC(hdc);
	m_MyCard_Black = (HBITMAP)LoadBitmap(hinst, MAKEINTRESOURCE(IDB_BITMAP11));
	m_OldCard_Black = (HBITMAP)SelectObject(MemDC_Black, m_MyCard_Black);

	BITMAP Bitmap_info_Black;
	GetObject(m_MyCard_Black, sizeof(Bitmap_info_Black), &Bitmap_info_Black);


	//// 뒤집은상태 (동물카드)
	MemDC = CreateCompatibleDC(hdc);
	m_MyCard = (HBITMAP)LoadBitmap(hinst, MAKEINTRESOURCE(card_number));
	m_OldCard = (HBITMAP)SelectObject(MemDC, m_MyCard);

	BITMAP Bitmap_info;
	GetObject(m_MyCard, sizeof(Bitmap_info), &Bitmap_info);

	m_size.cx = Bitmap_info.bmWidth;
	m_size.cy = Bitmap_info.bmHeight;

	m_posx = x; // 카드 출력위치
	m_posy = y;
	flip_over = FALSE; // 뒤집어진 상태
	card_clear = FALSE; // 카드 맞춘상태 유무
	rt = { m_posx, m_posy, m_posx + 125, m_posy + 210 }; // 범위저장

}

void Card::Re_Init(HINSTANCE hinst, int x, int y)
{

	m_MyCard_Black = (HBITMAP)LoadBitmap(hinst, MAKEINTRESOURCE(IDB_BITMAP11));
	m_OldCard_Black = (HBITMAP)SelectObject(MemDC_Black, m_MyCard_Black);

	BITMAP Bitmap_info_Black;
	GetObject(m_MyCard_Black, sizeof(Bitmap_info_Black), &Bitmap_info_Black);

	m_MyCard = (HBITMAP)LoadBitmap(hinst, MAKEINTRESOURCE(card_number));
	m_OldCard = (HBITMAP)SelectObject(MemDC, m_MyCard);

	BITMAP Bitmap_info;
	GetObject(m_MyCard, sizeof(Bitmap_info), &Bitmap_info);

	m_size.cx = Bitmap_info.bmWidth;
	m_size.cy = Bitmap_info.bmHeight;

	m_posx = x; // 카드 출력위치
	m_posy = y;
	flip_over = FALSE; // 뒤집어진 상태
	card_clear = FALSE; // 카드 맞춘상태 유무
	rt = { m_posx, m_posy, m_posx + 125, m_posy + 210 }; // 범위저장
}

void Card::Draw(HDC hdc, int SpX, int SpY)
{

	if (flip_over == FALSE) // 검은카드 상태
	{
		StretchBlt(hdc, m_posx, m_posy, m_size.cx * SpX - 15, m_size.cy * SpY - 15, MemDC_Black, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
	}
	else
	{
		StretchBlt(hdc, m_posx, m_posy, m_size.cx * SpX - 15, m_size.cy * SpY - 15, MemDC, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
	}

}

int Card::Click(Card _card, int x, int y)
{
	if (_card.rt.left <= x && _card.rt.right >= x && _card.rt.top <= y && _card.rt.bottom >= y && flip_over == FALSE)
	{
		flip_over = TRUE;
		return TRUE;
	}
	return FALSE;
}

Card::~Card()
{
	//// 여기 부분 살펴보기
	//SelectObject(MemDC, m_OldCard);
	//DeleteObject(m_MyCard);
	//DeleteDC(MemDC);

	//SelectObject(MemDC_Black, m_OldCard_Black);
	//DeleteObject(m_MyCard_Black);
	//DeleteDC(MemDC_Black);
}