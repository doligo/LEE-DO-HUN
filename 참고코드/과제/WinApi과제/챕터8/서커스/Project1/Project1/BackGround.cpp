#include "BackGround.h"

BackGround::BackGround()
{
	menu_select = 0;
	count_x = 0;
	count_y = 0;
	degree = 0;
	jump_trigger = FALSE;
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

	////////////////////////////////

	StageDC[0] = CreateCompatibleDC(hdc); // 검은배경
	m_StageBitMap[0] = CreateCompatibleBitmap(hdc, 1024, 533);
	m_Old_StageBitMap[0] = (HBITMAP)SelectObject(StageDC[0], m_StageBitMap[0]);

	StageDC[1] = CreateCompatibleDC(StageDC[0]);
	m_StageBitMap[1] = (HBITMAP)LoadImage(NULL, TEXT("ddd6.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_StageBitMap[1] = (HBITMAP)SelectObject(StageDC[1], m_StageBitMap[1]);
	GetObject(m_StageBitMap[1], sizeof(B_Info), &B_Info);
	m_Stagesize.cx = B_Info.bmWidth;
	m_Stagesize.cy = B_Info.bmHeight;

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

void BackGround::Init_Player(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);

	CharacterDC[0] = CreateCompatibleDC(GameDC[0]);
	m_CharacterBitMap[0] = (HBITMAP)LoadImage(NULL, TEXT("player0.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_CharacterBitMap[0] = (HBITMAP)SelectObject(CharacterDC[0], m_CharacterBitMap[0]);

	GetObject(m_CharacterBitMap[0], sizeof(B_Info), &B_Info); // 캐릭터이동
	m_Charactersize[0].cx = B_Info.bmWidth;
	m_Charactersize[0].cy = B_Info.bmHeight;

	///////////////////////////////////

	CharacterDC[1] = CreateCompatibleDC(GameDC[0]);
	m_CharacterBitMap[1] = (HBITMAP)LoadImage(NULL, TEXT("player1.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_CharacterBitMap[1] = (HBITMAP)SelectObject(CharacterDC[1], m_CharacterBitMap[1]);

	GetObject(m_CharacterBitMap[1], sizeof(B_Info), &B_Info); // 캐릭터뒷이동
	m_Charactersize[1].cx = B_Info.bmWidth;
	m_Charactersize[1].cy = B_Info.bmHeight;

	//////////////////////////////////////

	CharacterDC[2] = CreateCompatibleDC(GameDC[0]);
	m_CharacterBitMap[2] = (HBITMAP)LoadImage(NULL, TEXT("player2.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_CharacterBitMap[2] = (HBITMAP)SelectObject(CharacterDC[2], m_CharacterBitMap[2]);

	GetObject(m_CharacterBitMap[2], sizeof(B_Info), &B_Info); // 캐릭터앞이동, 점프
	m_Charactersize[2].cx = B_Info.bmWidth;
	m_Charactersize[2].cy = B_Info.bmHeight;

	/////////////////////////////////////////

	CharacterDC[3] = CreateCompatibleDC(GameDC[0]);
	m_CharacterBitMap[3] = (HBITMAP)LoadImage(NULL, TEXT("die.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_CharacterBitMap[3] = (HBITMAP)SelectObject(CharacterDC[3], m_CharacterBitMap[3]);

	GetObject(m_CharacterBitMap[3], sizeof(B_Info), &B_Info); // 캐릭터죽음
	m_Charactersize[3].cx = B_Info.bmWidth;
	m_Charactersize[3].cy = B_Info.bmHeight;

	///////////////////////////

	CharacterDC[4] = CreateCompatibleDC(GameDC[0]);
	m_CharacterBitMap[4] = (HBITMAP)LoadImage(NULL, TEXT("win.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_CharacterBitMap[4] = (HBITMAP)SelectObject(CharacterDC[4], m_CharacterBitMap[4]);

	GetObject(m_CharacterBitMap[4], sizeof(B_Info), &B_Info); // 캐릭터승리
	m_Charactersize[4].cx = B_Info.bmWidth;
	m_Charactersize[4].cy = B_Info.bmHeight;

	///////////////////////////

	CharacterDC[5] = CreateCompatibleDC(GameDC[0]);
	m_CharacterBitMap[5] = (HBITMAP)LoadImage(NULL, TEXT("win2.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_CharacterBitMap[5] = (HBITMAP)SelectObject(CharacterDC[5], m_CharacterBitMap[5]);

	GetObject(m_CharacterBitMap[5], sizeof(B_Info), &B_Info); // 캐릭터승리2
	m_Charactersize[5].cx = B_Info.bmWidth;
	m_Charactersize[5].cy = B_Info.bmHeight;

	player_x = 0;
	player_y = 385;
	player_pose = 0;
	jump_x = 0;
	jump_y = 0;
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
	{
		value = 10;
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		value = 20;
	}
	else if (GetKeyState(VK_RETURN) & 0x8000)
		return 30;

	menu_select = value;
}

void BackGround::Draw_GameScreen(HDC hdc)
{
	int _x = 0; // 캐릭터 움직일떄마다 배경도 -나 + 해주기
	int _y = 0;

	TransparentBlt(GameDC[0], 0, 210, m_Gamesize[0].cx * 16, m_Gamesize[0].cy + 150, GameDC[1], 0, 0, m_Gamesize[0].cx, m_Gamesize[0].cy, SRCCOPY); // 초록색배경

	for (int i = 0; i < 13; i++)
	{
		if (i == 2)
		{
			TransparentBlt(GameDC[0], _x, 115, m_Gamesize[1].cx + 30, m_Gamesize[1].cy + 30, GameDC[2], 0, 0, m_Gamesize[1].cx, m_Gamesize[1].cy, SRCCOPY); // 코끼리
		}
		else
		{
			TransparentBlt(GameDC[0], _x, 115, m_Gamesize[2].cx + 30, m_Gamesize[2].cy + 30, GameDC[3], 0, 0, m_Gamesize[2].cx, m_Gamesize[2].cy, SRCCOPY);
		}
		_x += 90;
	}

	Draw_Character(hdc);

	BitBlt(hdc, 0, 0, 1024, 533, GameDC[0], 0, 0, SRCCOPY);
}

void BackGround::Draw_StageScreen(HDC hdc)
{
	TransparentBlt(StageDC[0], 450, 200, m_Stagesize.cx, m_Stagesize.cy, StageDC[1], 0, 0, m_Stagesize.cx, m_Stagesize.cy, SRCCOPY);
	BitBlt(hdc, 0, 0, 1024, 533, StageDC[0], 0, 0, SRCCOPY);
}

void BackGround::Draw_Character(HDC hdc)
{
	TransparentBlt(GameDC[0], player_x, player_y + jump_y, m_Charactersize[0].cx + 10, m_Charactersize[0].cy + 25, CharacterDC[player_pose], 0, 0, m_Charactersize[0].cx, m_Charactersize[0].cy, RGB(255, 0, 255));
}

void BackGround::Control_Character()
{

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		player_x -= 1;
		count_x++;
		if (count_x >= 20)
		{
			if (player_pose == 0)
				player_pose = 1;
			else
				player_pose = 0;

			count_x = 0;
		}
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		player_x += 1;
		count_y++;
		if (count_y >= 20)
		{
			if (player_pose == 0)
				player_pose = 2;
			else
				player_pose = 0;

			count_y = 0;
		}
	}
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		player_pose = 2;
		jump_trigger = TRUE;
	}

	if (jump_trigger == TRUE)
	{
		degree += 1;
		if (degree == 180)
		{
			degree = 0;
			player_pose = 0;
			jump_trigger = FALSE;
		}
		jump_y = sin(degree * 3.14 / 180) * -130;
	}

}

BackGround::~BackGround()
{
	for (int i = 0; i < 9; i++)
	{
		DeleteObject(m_BitMap[i]);
		DeleteObject(m_Old_BitMap[i]);
		DeleteDC(MemDC[i]);
	}
	for (int i = 0; i < 2; i++)
	{
		DeleteObject(m_StageBitMap[i]);
		DeleteObject(m_Old_StageBitMap[i]);
		DeleteDC(StageDC[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		DeleteObject(m_GameBitMap[i]);
		DeleteObject(m_Old_GameBitMap[i]);
		DeleteDC(GameDC[i]);
	}
	for (int i = 0; i < 6; i++)
	{
		DeleteObject(m_CharacterBitMap[i]);
		DeleteObject(m_Old_CharacterBitMap[i]);
		DeleteDC(CharacterDC[i]);
	}
}