#include "BackGround.h"

BackGround::BackGround()
{

}

void BackGround::Init_BackGround(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);

	MemDC[0] = CreateCompatibleDC(hdc); // 검은배경
	m_BitMap[0] = CreateCompatibleBitmap(hdc, 1024, 533);
	m_Old_BitMap[0] = (HBITMAP)SelectObject(MemDC[0], m_BitMap[0]);
	
	/////////////////////////////

	MemDC[1] = CreateCompatibleDC(MemDC[0]);
	m_BitMap[1] = (HBITMAP)LoadImage(NULL, TEXT("star.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_BitMap[1] = (HBITMAP)SelectObject(MemDC[1], m_BitMap[1]);

	GetObject(m_BitMap[1], sizeof(B_Info), &B_Info); // 별의 크기
	m_size[0].cx = B_Info.bmWidth;
	m_size[0].cy = B_Info.bmHeight;

	/////////////////////////////

	MemDC[2] = CreateCompatibleDC(MemDC[0]);
	m_BitMap[2] = (HBITMAP)LoadImage(NULL, TEXT("star1.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_BitMap[2] = (HBITMAP)SelectObject(MemDC[2], m_BitMap[2]);

	GetObject(m_BitMap[2], sizeof(B_Info), &B_Info); // 별1의 크기
	m_size[1].cx = B_Info.bmWidth;
	m_size[1].cy = B_Info.bmHeight;

	/////////////////////////////

	MemDC[3] = CreateCompatibleDC(MemDC[0]);
	m_BitMap[3] = (HBITMAP)LoadImage(NULL, TEXT("star2.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_BitMap[3] = (HBITMAP)SelectObject(MemDC[3], m_BitMap[3]);

	GetObject(m_BitMap[3], sizeof(B_Info), &B_Info); // 별2의 크기
	m_size[2].cx = B_Info.bmWidth;
	m_size[2].cy = B_Info.bmHeight;

	////////////////////////////////

	MemDC[4] = CreateCompatibleDC(MemDC[0]);
	m_BitMap[4] = (HBITMAP)LoadImage(NULL, TEXT("ddd.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_BitMap[4] = (HBITMAP)SelectObject(MemDC[4], m_BitMap[4]);

	GetObject(m_BitMap[4], sizeof(B_Info), &B_Info); // 타이틀 화면로고
	m_size[3].cx = B_Info.bmWidth;
	m_size[3].cy = B_Info.bmHeight;
}

void BackGround::Draw_TitleScreen(HDC hdc)
{
	int _x = 0;

	static int x_x = 375;

	TransparentBlt(MemDC[0], 400, 50, m_size[3].cx, m_size[3].cy, MemDC[4], 0, 0, m_size[3].cx, m_size[3].cy, RGB(0, 0, 0));

	for (int i = 0; i < 5; i++)
	{
		TransparentBlt(MemDC[0], 390 + _x, 140, m_size[0].cx, m_size[0].cy, MemDC[1], 0, 0, m_size[0].cx, m_size[0].cy, RGB(255, 0, 255));
		_x += 15;
		TransparentBlt(MemDC[0], 390 + _x, 140, m_size[1].cx, m_size[1].cy, MemDC[2], 0, 0, m_size[1].cx, m_size[1].cy, RGB(255, 0, 255));
		_x += 15;
		TransparentBlt(MemDC[0], 390 + _x, 140, m_size[2].cx, m_size[2].cy, MemDC[3], 0, 0, m_size[2].cx, m_size[2].cy, RGB(255, 0, 255));
		_x += 15;
	}

	BitBlt(hdc, 0, 0, 1024, 533, MemDC[0], 0, 0, SRCCOPY);
}

BackGround::~BackGround()
{
	
	for (int i = 0; i < 5; i++)
	{
		DeleteObject(m_BitMap[i]);
		DeleteObject(m_Old_BitMap[i]);
		DeleteDC(MemDC[i]);
	}
}