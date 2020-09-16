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

	////////////////////////////////

	MemDC[5] = CreateCompatibleDC(MemDC[0]);
	m_BitMap[5] = (HBITMAP)LoadImage(NULL, TEXT("ddd2.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_BitMap[5] = (HBITMAP)SelectObject(MemDC[5], m_BitMap[5]);

	GetObject(m_BitMap[5], sizeof(B_Info), &B_Info); // 시작
	m_size[4].cx = B_Info.bmWidth;
	m_size[4].cy = B_Info.bmHeight;

	////////////////////////////////

	MemDC[6] = CreateCompatibleDC(MemDC[0]);
	m_BitMap[6] = (HBITMAP)LoadImage(NULL, TEXT("ddd3.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_BitMap[6] = (HBITMAP)SelectObject(MemDC[6], m_BitMap[6]);

	GetObject(m_BitMap[6], sizeof(B_Info), &B_Info); // 종료
	m_size[5].cx = B_Info.bmWidth;
	m_size[5].cy = B_Info.bmHeight;

	////////////////////////////////

	MemDC[7] = CreateCompatibleDC(MemDC[0]);
	m_BitMap[7] = (HBITMAP)LoadImage(NULL, TEXT("ddd4.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_BitMap[7] = (HBITMAP)SelectObject(MemDC[7], m_BitMap[7]);

	GetObject(m_BitMap[7], sizeof(B_Info), &B_Info); // 화살표
	m_size[6].cx = B_Info.bmWidth;
	m_size[6].cy = B_Info.bmHeight;

	////////////////////////////////

	MemDC[8] = CreateCompatibleDC(MemDC[0]);
	m_BitMap[8] = (HBITMAP)LoadImage(NULL, TEXT("ddd5.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_BitMap[8] = (HBITMAP)SelectObject(MemDC[8], m_BitMap[8]);

	GetObject(m_BitMap[8], sizeof(B_Info), &B_Info); // 화살표 가리는용
	m_size[7].cx = B_Info.bmWidth;
	m_size[7].cy = B_Info.bmHeight;

	//////////////////////////////////////////////////////////////////// 여기서부터는 게임화면**

	GameDC[0] = CreateCompatibleDC(hdc); // 검은배경
	m_GameBitMap[0] = CreateCompatibleBitmap(hdc, 1024, 533);
	m_Old_GameBitMap[0] = (HBITMAP)SelectObject(GameDC[0], m_GameBitMap[0]);

	//////////////////////////////

	GameDC[1] = CreateCompatibleDC(GameDC[0]);
	m_GameBitMap[1] = (HBITMAP)LoadImage(NULL, TEXT("back.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_GameBitMap[1] = (HBITMAP)SelectObject(GameDC[1], m_GameBitMap[1]);

	GetObject(m_GameBitMap[1], sizeof(B_Info), &B_Info);
	m_Gamesize[0].cx = B_Info.bmWidth;
	m_Gamesize[0].cy = B_Info.bmHeight;

	///////////////////////////////

	GameDC[2] = CreateCompatibleDC(GameDC[0]);
	m_GameBitMap[2] = (HBITMAP)LoadImage(NULL, TEXT("back_deco.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_GameBitMap[2] = (HBITMAP)SelectObject(GameDC[2], m_GameBitMap[2]);

	GetObject(m_GameBitMap[2], sizeof(B_Info), &B_Info);
	m_Gamesize[1].cx = B_Info.bmWidth;
	m_Gamesize[1].cy = B_Info.bmHeight;

	////////////////////////////////

	GameDC[3] = CreateCompatibleDC(GameDC[0]);
	m_GameBitMap[3] = (HBITMAP)LoadImage(NULL, TEXT("back_normal.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_GameBitMap[3] = (HBITMAP)SelectObject(GameDC[3], m_GameBitMap[3]);

	GetObject(m_GameBitMap[3], sizeof(B_Info), &B_Info);
	m_Gamesize[2].cx = B_Info.bmWidth;
	m_Gamesize[2].cy = B_Info.bmHeight;
}

int BackGround::Draw_TitleScreen(HDC hdc)
{
	int _x = 390;
	int _y = 145;
	static int value = 10;

	TransparentBlt(MemDC[0], 400, 50, m_size[3].cx, m_size[3].cy, MemDC[4], 0, 0, m_size[3].cx, m_size[3].cy, RGB(0, 0, 0));
	TransparentBlt(MemDC[0], 450, 250, m_size[4].cx, m_size[4].cy, MemDC[5], 0, 0, m_size[4].cx, m_size[4].cy, RGB(0, 0, 0));
	TransparentBlt(MemDC[0], 450, 320, m_size[5].cx, m_size[5].cy, MemDC[6], 0, 0, m_size[5].cx, m_size[5].cy, RGB(0, 0, 0));

	if (value == 10)
	{
		TransparentBlt(MemDC[0], 350, 250, m_size[6].cx, m_size[6].cy, MemDC[7], 0, 0, m_size[6].cx, m_size[6].cy, RGB(0, 0, 0));
		TransparentBlt(MemDC[0], 350, 320, m_size[7].cx, m_size[7].cy, MemDC[8], 0, 0, m_size[7].cx, m_size[7].cy, SRCCOPY);
	}
	else if (value == 20)
	{
		TransparentBlt(MemDC[0], 350, 320, m_size[6].cx, m_size[6].cy, MemDC[7], 0, 0, m_size[6].cx, m_size[6].cy, RGB(0, 0, 0));
		TransparentBlt(MemDC[0], 350, 250, m_size[7].cx, m_size[7].cy, MemDC[8], 0, 0, m_size[7].cx, m_size[7].cy, SRCCOPY);
	}

	for (int i = 0; i < 5; i++)
	{
		TransparentBlt(MemDC[0], _x, _y, m_size[0].cx, m_size[0].cy, MemDC[rand() % 4], 0, 0, m_size[0].cx, m_size[0].cy, RGB(255, 0, 255));
		_x += 15;
		TransparentBlt(MemDC[0], _x, _y, m_size[1].cx, m_size[1].cy, MemDC[rand() % 4], 0, 0, m_size[1].cx, m_size[1].cy, RGB(255, 0, 255));
		_x += 15;
		TransparentBlt(MemDC[0], _x, _y, m_size[2].cx, m_size[2].cy, MemDC[rand() % 4], 0, 0, m_size[2].cx, m_size[2].cy, RGB(255, 0, 255));
		_x += 15;
	}
	_x = 390;
	_y -= 100;
	for (int i = 0; i < 5; i++)
	{
		TransparentBlt(MemDC[0], _x, _y, m_size[0].cx, m_size[0].cy, MemDC[rand() % 4], 0, 0, m_size[0].cx, m_size[0].cy, RGB(255, 0, 255));
		_x += 15;
		TransparentBlt(MemDC[0], _x, _y, m_size[1].cx, m_size[1].cy, MemDC[rand() % 4], 0, 0, m_size[1].cx, m_size[1].cy, RGB(255, 0, 255));
		_x += 15;
		TransparentBlt(MemDC[0], _x, _y, m_size[2].cx, m_size[2].cy, MemDC[rand() % 4], 0, 0, m_size[2].cx, m_size[2].cy, RGB(255, 0, 255));
		_x += 15;
	}
	_x = 390;
	_y = 57;
	for (int i = 0; i < 2; i++)
	{
		TransparentBlt(MemDC[0], _x, _y, m_size[0].cx, m_size[0].cy, MemDC[rand() % 4], 0, 0, m_size[0].cx, m_size[0].cy, RGB(255, 0, 255));
		_y += 15;
		TransparentBlt(MemDC[0], _x, _y, m_size[1].cx, m_size[1].cy, MemDC[rand() % 4], 0, 0, m_size[1].cx, m_size[1].cy, RGB(255, 0, 255));
		_y += 15;
		TransparentBlt(MemDC[0], _x, _y, m_size[2].cx, m_size[2].cy, MemDC[rand() % 4], 0, 0, m_size[2].cx, m_size[2].cy, RGB(255, 0, 255));
		_y += 15;
	}
	_x = 600;
	_y = 57;
	for (int i = 0; i < 2; i++)
	{
		TransparentBlt(MemDC[0], _x, _y, m_size[0].cx, m_size[0].cy, MemDC[rand() % 4], 0, 0, m_size[0].cx, m_size[0].cy, RGB(255, 0, 255));
		_y += 15;
		TransparentBlt(MemDC[0], _x, _y, m_size[1].cx, m_size[1].cy, MemDC[rand() % 4], 0, 0, m_size[1].cx, m_size[1].cy, RGB(255, 0, 255));
		_y += 15;
		TransparentBlt(MemDC[0], _x, _y, m_size[2].cx, m_size[2].cy, MemDC[rand() % 4], 0, 0, m_size[2].cx, m_size[2].cy, RGB(255, 0, 255));
		_y += 15;
	}

	BitBlt(hdc, 0, 0, 1024, 533, MemDC[0], 0, 0, SRCCOPY);

	if (GetKeyState(VK_UP) & 0x8000)
		value = 10;
	else if (GetKeyState(VK_DOWN) & 0x8000)
		value = 20;
	else if (GetKeyState(VK_RETURN) & 0x8000)
		return 30;
}

void BackGround::Draw_GameScreen(HDC hdc)
{
	int _x = 0; // 캐릭터 움직일떄마다 -나 + 해주기
	int _y = 0;

	TransparentBlt(GameDC[0], 0, 210, m_Gamesize[0].cx * 16, m_Gamesize[0].cy + 150, GameDC[1], 0, 0, m_Gamesize[0].cx, m_Gamesize[0].cy, SRCCOPY); // 초록색배경

	TransparentBlt(GameDC[0], _x, 115, m_Gamesize[2].cx + 30, m_Gamesize[2].cy + 30, GameDC[3], 0, 0, m_Gamesize[2].cx, m_Gamesize[2].cy, SRCCOPY);
	TransparentBlt(GameDC[0], 90, 115, m_Gamesize[2].cx + 30, m_Gamesize[2].cy + 30, GameDC[3], 0, 0, m_Gamesize[2].cx, m_Gamesize[2].cy, SRCCOPY);
	TransparentBlt(GameDC[0], 180, 115, m_Gamesize[1].cx + 30, m_Gamesize[1].cy + 30, GameDC[2], 0, 0, m_Gamesize[1].cx, m_Gamesize[1].cy, SRCCOPY); // 코끼리
	TransparentBlt(GameDC[0], 270, 115, m_Gamesize[2].cx + 30, m_Gamesize[2].cy + 30, GameDC[3], 0, 0, m_Gamesize[2].cx, m_Gamesize[2].cy, SRCCOPY);
	TransparentBlt(GameDC[0], 360, 115, m_Gamesize[2].cx + 30, m_Gamesize[2].cy + 30, GameDC[3], 0, 0, m_Gamesize[2].cx, m_Gamesize[2].cy, SRCCOPY);
	TransparentBlt(GameDC[0], 450, 115, m_Gamesize[2].cx + 30, m_Gamesize[2].cy + 30, GameDC[3], 0, 0, m_Gamesize[2].cx, m_Gamesize[2].cy, SRCCOPY);
	TransparentBlt(GameDC[0], 540, 115, m_Gamesize[2].cx + 30, m_Gamesize[2].cy + 30, GameDC[3], 0, 0, m_Gamesize[2].cx, m_Gamesize[2].cy, SRCCOPY);
	TransparentBlt(GameDC[0], 630, 115, m_Gamesize[2].cx + 30, m_Gamesize[2].cy + 30, GameDC[3], 0, 0, m_Gamesize[2].cx, m_Gamesize[2].cy, SRCCOPY);
	TransparentBlt(GameDC[0], 720, 115, m_Gamesize[2].cx + 30, m_Gamesize[2].cy + 30, GameDC[3], 0, 0, m_Gamesize[2].cx, m_Gamesize[2].cy, SRCCOPY);
	TransparentBlt(GameDC[0], 810, 115, m_Gamesize[2].cx + 30, m_Gamesize[2].cy + 30, GameDC[3], 0, 0, m_Gamesize[2].cx, m_Gamesize[2].cy, SRCCOPY);
	TransparentBlt(GameDC[0], 900, 115, m_Gamesize[2].cx + 30, m_Gamesize[2].cy + 30, GameDC[3], 0, 0, m_Gamesize[2].cx, m_Gamesize[2].cy, SRCCOPY);
	TransparentBlt(GameDC[0], 990, 115, m_Gamesize[2].cx + 30, m_Gamesize[2].cy + 30, GameDC[3], 0, 0, m_Gamesize[2].cx, m_Gamesize[2].cy, SRCCOPY);

	BitBlt(hdc, 0, 0, 1024, 533, GameDC[0], 0, 0, SRCCOPY);
}

BackGround::~BackGround()
{
	
	for (int i = 0; i < 9; i++)
	{
		DeleteObject(m_BitMap[i]);
		DeleteObject(m_Old_BitMap[i]);
		DeleteDC(MemDC[i]);
	}
}