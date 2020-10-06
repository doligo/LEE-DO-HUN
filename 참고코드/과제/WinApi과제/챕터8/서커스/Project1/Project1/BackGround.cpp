#include "BackGround.h"

BackGround::BackGround()
{
	menu_select = 0;
	count_x = 0;
	count_x2 = 0;
	degree = 0;
	ring_draw = FALSE;
	front_draw = FALSE;
	enemy_change_count = 0;
	enemy_change_count_2 = 0;
	jump_trigger = FALSE;
	die_check = FALSE;
	first_ring_created = FALSE;
	second_ring_created = FALSE;
	first_front_created = FALSE;
	second_front_created = FALSE;
	select_money1 = FALSE;
	select_money2 = FALSE;
	save_x = 0;
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

	//////////////////////////////////////////////////////////////////// 여기서부터는 게임화면

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

	/////////////////////////////////

	GameDC[4] = CreateCompatibleDC(GameDC[0]);
	m_GameBitMap[4] = (HBITMAP)LoadImage(NULL, TEXT("cash.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_GameBitMap[4] = (HBITMAP)SelectObject(GameDC[4], m_GameBitMap[4]);

	GetObject(m_GameBitMap[4], sizeof(B_Info), &B_Info);
	m_Gamesize[3].cx = B_Info.bmWidth;
	m_Gamesize[3].cy = B_Info.bmHeight;

	/////////////////////////////////

	GameDC[5] = CreateCompatibleDC(GameDC[0]);
	m_GameBitMap[5] = (HBITMAP)LoadImage(NULL, TEXT("miter.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_GameBitMap[5] = (HBITMAP)SelectObject(GameDC[5], m_GameBitMap[5]);

	GetObject(m_GameBitMap[5], sizeof(B_Info), &B_Info);
	m_Gamesize[4].cx = B_Info.bmWidth;
	m_Gamesize[4].cy = B_Info.bmHeight;

	//////////////////////////////////

	GameDC[6] = CreateCompatibleDC(GameDC[0]);
	m_GameBitMap[6] = (HBITMAP)LoadImage(NULL, TEXT("end.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_GameBitMap[6] = (HBITMAP)SelectObject(GameDC[6], m_GameBitMap[6]);

	GetObject(m_GameBitMap[6], sizeof(B_Info), &B_Info);
	m_Gamesize[5].cx = B_Info.bmWidth;
	m_Gamesize[5].cy = B_Info.bmHeight;

	back_ground_x = 0;
	back_ground_y = 115;
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

	player_x = 350;
	player_y = 385;
	player_rt_y = 385;
	player_pose = 0;
	jump_x = 0;
	jump_y = 0;
	m_Player_rt = { player_x, player_rt_y, player_x + 10, player_rt_y + 60 };
}

void BackGround::Init_Enemy(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);

	EnemyDC[0] = CreateCompatibleDC(GameDC[0]);
	m_EnemyBitMap[0] = (HBITMAP)LoadImage(NULL, TEXT("enemy.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_EnemyBitMap[0] = (HBITMAP)SelectObject(EnemyDC[0], m_EnemyBitMap[0]);

	GetObject(m_EnemyBitMap[0], sizeof(B_Info), &B_Info); // 불타는 링
	m_Enemysize[0].cx = B_Info.bmWidth;
	m_Enemysize[0].cy = B_Info.bmHeight;

	//////////////////////

	EnemyDC[1] = CreateCompatibleDC(GameDC[0]);
	m_EnemyBitMap[1] = (HBITMAP)LoadImage(NULL, TEXT("enemy_b.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_EnemyBitMap[1] = (HBITMAP)SelectObject(EnemyDC[1], m_EnemyBitMap[1]);

	GetObject(m_EnemyBitMap[1], sizeof(B_Info), &B_Info); // 불타는 링_back
	m_Enemysize[1].cx = B_Info.bmWidth;
	m_Enemysize[1].cy = B_Info.bmHeight;

	///////////////////////////

	EnemyDC[2] = CreateCompatibleDC(GameDC[0]);
	m_EnemyBitMap[2] = (HBITMAP)LoadImage(NULL, TEXT("enemy_f.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_EnemyBitMap[2] = (HBITMAP)SelectObject(EnemyDC[2], m_EnemyBitMap[2]);

	GetObject(m_EnemyBitMap[2], sizeof(B_Info), &B_Info); // 불타는 링_front
	m_Enemysize[2].cx = B_Info.bmWidth;
	m_Enemysize[2].cy = B_Info.bmHeight;

	///////////////////////////

	EnemyDC[3] = CreateCompatibleDC(GameDC[0]);
	m_EnemyBitMap[3] = (HBITMAP)LoadImage(NULL, TEXT("enemy1.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_EnemyBitMap[3] = (HBITMAP)SelectObject(EnemyDC[3], m_EnemyBitMap[3]);

	GetObject(m_EnemyBitMap[3], sizeof(B_Info), &B_Info); // 불타는 링2
	m_Enemysize[3].cx = B_Info.bmWidth;
	m_Enemysize[3].cy = B_Info.bmHeight;

	///////////////////////////

	EnemyDC[4] = CreateCompatibleDC(GameDC[0]);
	m_EnemyBitMap[4] = (HBITMAP)LoadImage(NULL, TEXT("enemy_1b.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_EnemyBitMap[4] = (HBITMAP)SelectObject(EnemyDC[4], m_EnemyBitMap[4]);

	GetObject(m_EnemyBitMap[4], sizeof(B_Info), &B_Info); // 불타는 링2_back
	m_Enemysize[4].cx = B_Info.bmWidth;
	m_Enemysize[4].cy = B_Info.bmHeight;

	///////////////////////////////

	EnemyDC[5] = CreateCompatibleDC(GameDC[0]);
	m_EnemyBitMap[5] = (HBITMAP)LoadImage(NULL, TEXT("enemy_1f.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_EnemyBitMap[5] = (HBITMAP)SelectObject(EnemyDC[5], m_EnemyBitMap[5]);

	GetObject(m_EnemyBitMap[5], sizeof(B_Info), &B_Info); // 불타는 링2_front
	m_Enemysize[5].cx = B_Info.bmWidth;
	m_Enemysize[5].cy = B_Info.bmHeight;

	///////////////////////////////////

	EnemyDC[6] = CreateCompatibleDC(GameDC[0]);
	m_EnemyBitMap[6] = (HBITMAP)LoadImage(NULL, TEXT("enemy_l.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_EnemyBitMap[6] = (HBITMAP)SelectObject(EnemyDC[6], m_EnemyBitMap[6]);

	GetObject(m_EnemyBitMap[6], sizeof(B_Info), &B_Info); // 불타는 링3(돈)
	m_Enemysize[6].cx = B_Info.bmWidth;
	m_Enemysize[6].cy = B_Info.bmHeight;

	/////////////////////////////////

	EnemyDC[7] = CreateCompatibleDC(GameDC[0]);
	m_EnemyBitMap[7] = (HBITMAP)LoadImage(NULL, TEXT("enemy_l_b.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_EnemyBitMap[7] = (HBITMAP)SelectObject(EnemyDC[7], m_EnemyBitMap[7]);

	GetObject(m_EnemyBitMap[7], sizeof(B_Info), &B_Info); // 불타는 링3(돈)_back
	m_Enemysize[7].cx = B_Info.bmWidth;
	m_Enemysize[7].cy = B_Info.bmHeight;

	////////////////////////////////

	EnemyDC[8] = CreateCompatibleDC(GameDC[0]);
	m_EnemyBitMap[8] = (HBITMAP)LoadImage(NULL, TEXT("enemy_l_f.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_EnemyBitMap[8] = (HBITMAP)SelectObject(EnemyDC[8], m_EnemyBitMap[8]);

	GetObject(m_EnemyBitMap[8], sizeof(B_Info), &B_Info); // 불타는 링3(돈)_front
	m_Enemysize[8].cx = B_Info.bmWidth;
	m_Enemysize[8].cy = B_Info.bmHeight;

	///////////////////////////////

	EnemyDC[9] = CreateCompatibleDC(GameDC[0]);
	m_EnemyBitMap[9] = (HBITMAP)LoadImage(NULL, TEXT("front.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_EnemyBitMap[9] = (HBITMAP)SelectObject(EnemyDC[9], m_EnemyBitMap[9]);

	GetObject(m_EnemyBitMap[9], sizeof(B_Info), &B_Info); // 항아리불
	m_Enemysize[9].cx = B_Info.bmWidth;
	m_Enemysize[9].cy = B_Info.bmHeight;

	/////////////////////////////////////

	EnemyDC[10] = CreateCompatibleDC(GameDC[0]);
	m_EnemyBitMap[10] = (HBITMAP)LoadImage(NULL, TEXT("front2.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Old_EnemyBitMap[10] = (HBITMAP)SelectObject(EnemyDC[10], m_EnemyBitMap[10]);

	GetObject(m_EnemyBitMap[10], sizeof(B_Info), &B_Info); // 항아리불2
	m_Enemysize[10].cx = B_Info.bmWidth;
	m_Enemysize[10].cy = B_Info.bmHeight;

	m_Enemy_rt[0] = { 0, 0, 0, 0 };
	m_Enemy_rt[1] = { 0, 0, 0, 0 };
	m_Front_rt = { 0, 0, 0, 0 };
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
	int _x = 0;
	int _y = 0;

	TransparentBlt(GameDC[0], 0, 210, m_Gamesize[0].cx * 16, m_Gamesize[0].cy + 150, GameDC[1], 0, 0, m_Gamesize[0].cx, m_Gamesize[0].cy, SRCCOPY); // 초록색배경

	if (player_x <= END_MAP)
	{
		for (int i = 0; i < 77; i++)
		{
			if (i == 2 || i == 15 || i == 28 || i == 41 || i == 54 || i == 67)
			{
				TransparentBlt(GameDC[0], _x + back_ground_x, 115, m_Gamesize[1].cx + 30, m_Gamesize[1].cy + 30, GameDC[2], 0, 0, m_Gamesize[1].cx, m_Gamesize[1].cy, SRCCOPY); // 코끼리
			}
			else
			{
				TransparentBlt(GameDC[0], _x + back_ground_x, 115, m_Gamesize[2].cx + 30, m_Gamesize[2].cy + 30, GameDC[3], 0, 0, m_Gamesize[2].cx, m_Gamesize[2].cy, SRCCOPY);
			}
			_x += 90;
		}
		TransparentBlt(GameDC[0], 6800 + back_ground_x, 390, m_Gamesize[5].cx + 20, m_Gamesize[5].cy + 30, GameDC[6], 0, 0, m_Gamesize[5].cx, m_Gamesize[5].cy, RGB(255, 0, 255)); //end

		save_x = 6800 + back_ground_x;
	}
	else
	{
		for (int i = 0; i < 13; i++)
		{
			if (i == 2)
			{
				TransparentBlt(GameDC[0], _x + save_x - 950, 115, m_Gamesize[1].cx + 30, m_Gamesize[1].cy + 30, GameDC[2], 0, 0, m_Gamesize[1].cx, m_Gamesize[1].cy, SRCCOPY); // 코끼리
			}
			else
			{
				TransparentBlt(GameDC[0], _x + save_x - 950, 115, m_Gamesize[2].cx + 30, m_Gamesize[2].cy + 30, GameDC[3], 0, 0, m_Gamesize[2].cx, m_Gamesize[2].cy, SRCCOPY);
			}
			_x += 90;
		}
		TransparentBlt(GameDC[0], save_x, 390, m_Gamesize[5].cx + 20, m_Gamesize[5].cy + 30, GameDC[6], 0, 0, m_Gamesize[5].cx, m_Gamesize[5].cy, RGB(255, 0, 255)); //end
	}

	Draw_Miter();

	Draw_Character(hdc);
	Draw_Enemy(hdc);

	BitBlt(hdc, 0, 0, 1024, 533, GameDC[0], 0, 0, SRCCOPY);
}

void BackGround::Draw_StageScreen(HDC hdc)
{
	TransparentBlt(StageDC[0], 450, 200, m_Stagesize.cx, m_Stagesize.cy, StageDC[1], 0, 0, m_Stagesize.cx, m_Stagesize.cy, SRCCOPY);
	BitBlt(hdc, 0, 0, 1024, 533, StageDC[0], 0, 0, SRCCOPY);
}

void BackGround::Draw_Character(HDC hdc)
{
	TransparentBlt(GameDC[0], player_x + back_ground_x, player_y + jump_y, m_Charactersize[0].cx + 10, m_Charactersize[0].cy + 25, CharacterDC[player_pose], 0, 0, m_Charactersize[0].cx, m_Charactersize[0].cy, RGB(255, 0, 255));
}

void BackGround::Draw_Die_Character(HDC hdc)
{
	TransparentBlt(GameDC[0], player_x + back_ground_x, player_y + jump_y, m_Charactersize[3].cx + 10, m_Charactersize[3].cy + 25, CharacterDC[3], 0, 0, m_Charactersize[3].cx, m_Charactersize[3].cy, RGB(255, 0, 255));
	BitBlt(hdc, 0, 0, 1024, 533, GameDC[0], 0, 0, SRCCOPY);
}

void BackGround::Draw_Enemy(HDC hdc)
{
	///// fire ring back front 구별해서 그려주고
	//// 넘는순간 그리는 순서는 back -> 캐릭터 -> front 순으로 그려준다**
	static int enemy_move = 0;

	if (ring_draw == FALSE)
	{
		if (first_ring_created == TRUE)
		{
			TransparentBlt(GameDC[0], enemy_x[0] + back_ground_x, enemy_y[0], m_Enemysize[0].cx + 10, m_Enemysize[0].cy + 60, EnemyDC[0], 0, 0, m_Enemysize[0].cx, m_Enemysize[0].cy, RGB(255, 0, 255));
			if (select_money1 == 1)
				TransparentBlt(GameDC[0], money_x[0] + back_ground_x, money_y[0], m_Gamesize[3].cx + 10, m_Gamesize[3].cy + 10, GameDC[4], 0, 0, m_Gamesize[3].cx, m_Gamesize[3].cy, RGB(255, 0, 255));
		}
		if (second_ring_created == TRUE)
		{
			TransparentBlt(GameDC[0], enemy_x[1] + back_ground_x, enemy_y[1], m_Enemysize[0].cx + 10, m_Enemysize[0].cy + 60, EnemyDC[0], 0, 0, m_Enemysize[0].cx, m_Enemysize[0].cy, RGB(255, 0, 255));
			if (select_money2 == 1)
				TransparentBlt(GameDC[0], money_x[1] + back_ground_x, money_y[1], m_Gamesize[3].cx + 10, m_Gamesize[3].cy + 10, GameDC[4], 0, 0, m_Gamesize[3].cx, m_Gamesize[3].cy, RGB(255, 0, 255));
		}

		enemy_change_count++;
		if (enemy_change_count >= 30)
		{
			ring_draw = TRUE;
			enemy_change_count = 0;
		}
	}
	else if (ring_draw == TRUE)
	{
		if (first_ring_created == TRUE)
		{
			TransparentBlt(GameDC[0], enemy_x[0] + back_ground_x, enemy_y[0], m_Enemysize[3].cx + 10, m_Enemysize[3].cy + 60, EnemyDC[3], 0, 0, m_Enemysize[3].cx, m_Enemysize[3].cy, RGB(255, 0, 255));
			if (select_money1 == 1)
				TransparentBlt(GameDC[0], money_x[0] + back_ground_x, money_y[0], m_Gamesize[3].cx + 10, m_Gamesize[3].cy + 10, GameDC[4], 0, 0, m_Gamesize[3].cx, m_Gamesize[3].cy, RGB(255, 0, 255));
		}

		if (second_ring_created == TRUE)
		{
			TransparentBlt(GameDC[0], enemy_x[1] + back_ground_x, enemy_y[1], m_Enemysize[3].cx + 10, m_Enemysize[3].cy + 60, EnemyDC[3], 0, 0, m_Enemysize[3].cx, m_Enemysize[3].cy, RGB(255, 0, 255));
			if (select_money2 == 1)
				TransparentBlt(GameDC[0], money_x[1] + back_ground_x, money_y[1], m_Gamesize[3].cx + 10, m_Gamesize[3].cy + 10, GameDC[4], 0, 0, m_Gamesize[3].cx, m_Gamesize[3].cy, RGB(255, 0, 255));
		}

		enemy_change_count++;
		if (enemy_change_count >= 30)
		{
			ring_draw = FALSE;
			enemy_change_count = 0;
		}
	}
	//////////////////////////// 바로밑은 바닥불
	if (front_draw == FALSE)
	{
		if (first_front_created == TRUE)
		{
			TransparentBlt(GameDC[0], enemy_x_2 + back_ground_x, enemy_y_2, m_Enemysize[9].cx + 10, m_Enemysize[9].cy + 20, EnemyDC[9], 0, 0, m_Enemysize[9].cx, m_Enemysize[9].cy, RGB(255, 0, 255));
		}

		enemy_change_count_2++;
		if (enemy_change_count_2 >= 30)
		{
			front_draw = TRUE;
			enemy_change_count_2 = 0;
		}
	}
	else if (front_draw == TRUE)
	{
		if (first_front_created == TRUE)
		{
			TransparentBlt(GameDC[0], enemy_x_2 + back_ground_x, enemy_y_2, m_Enemysize[10].cx + 10, m_Enemysize[10].cy + 20, EnemyDC[10], 0, 0, m_Enemysize[10].cx, m_Enemysize[10].cy, RGB(255, 0, 255));
		}

		enemy_change_count_2++;
		if (enemy_change_count_2 >= 30)
		{
			front_draw = FALSE;
			enemy_change_count_2 = 0;
		}
	}

	enemy_move++;
	if (enemy_move >= 2)
	{
		if (first_ring_created == TRUE)
			enemy_x[0]--;
		if (second_ring_created == TRUE)
			enemy_x[1]--;

		enemy_move = 0;
	}

	m_Enemy_rt[0] = { enemy_x[0] - 15, enemy_y[0] + 170, enemy_x[0] - 10 + 40, enemy_y[0] + 160 + 30 };
	m_Enemy_rt[1] = { enemy_x[1] - 15, enemy_y[1] + 170, enemy_x[1] - 10 + 40, enemy_y[1] + 160 + 30 };

	m_Front_rt = { enemy_x_2, enemy_y_2, enemy_x_2 + 60, enemy_y_2 + 20 };
}

void BackGround::Draw_Miter()
{
	int num = 0;
	char buffer[256];

	for (int i = 0; i < 11; i++)
	{
		TransparentBlt(GameDC[0], 290 + back_ground_x + num, 485, m_Gamesize[4].cx + 10, m_Gamesize[4].cy + 10, GameDC[5], 0, 0, m_Gamesize[4].cx, m_Gamesize[4].cy, RGB(255, 0, 255));

		RECT rt = { 300 + num + back_ground_x, 495, 300 + num + back_ground_x + 60, 495 + 20 };
		sprintf_s(buffer, "%d", (100 - 10 * i));
		DrawText(GameDC[0], buffer, -1, &rt, DT_CENTER | DT_WORDBREAK);

		num += 650;
	}
}

void BackGround::Control_Character()
{

	Set_Ring(); // 링 반복생성
	Set_Front();
	Die_Check();

	if (jump_trigger == FALSE)
	{
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			if (player_x >= 350)
			{
				player_x -= 1;
				count_x++;

				if (player_x <= END_MAP)
					back_ground_x += 1;
			}

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
			count_x2++;

			if (player_x <= END_MAP)
				back_ground_x -= 1;

			if (count_x2 >= 20)
			{
				if (player_pose == 0)
					player_pose = 2;
				else
					player_pose = 0;

				count_x2 = 0;
			}
		}
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			player_pose = 2;
			jump_trigger = TRUE;
		}
	}


	if (jump_trigger == TRUE)
	{
		degree += 1;
		player_rt_y -= 1;
		player_x += 1;

		if (player_x <= END_MAP)
			back_ground_x -= 1;

		if (degree == 180)
		{
			degree = 0;
			player_pose = 0;
			jump_trigger = FALSE;
		}
		jump_y = sin(degree * 3.14 / 180) * -130;
	}

	if (player_rt_y != 385 && jump_trigger == FALSE)
	{
		player_rt_y += 1;
	}

	m_Player_rt = { player_x, player_rt_y, player_x + 10, player_rt_y + 60 };

}

void BackGround::Set_Ring()
{
	static int trigger = FALSE;

	if (trigger == FALSE)
	{
		trigger = TRUE;
		select_money1 = rand() % 3;
		Set_Enemy_Pos(0);
		first_ring_created = TRUE;
	}

	if (second_ring_created == TRUE && first_ring_created == FALSE && player_x >= enemy_x[1])
	{
		select_money1 = rand() % 3;
		Set_Enemy_Pos(0);
		first_ring_created = TRUE;
	}
	else if (first_ring_created == TRUE && second_ring_created == FALSE && player_x >= enemy_x[0])
	{
		select_money2 = rand() % 3;
		Set_Enemy_Pos(1);
		second_ring_created = TRUE;
	}

	if (m_Player_rt.left >= enemy_x[0] + 300)
	{
		first_ring_created = FALSE;
		select_money1 = FALSE;
	}
	else if (m_Player_rt.left >= enemy_x[1] + 300)
	{
		second_ring_created = FALSE;
		select_money2 = FALSE;
	}

	if (select_money1 == 1) // 돈주머니 좌표설정
	{
		money_x[0] = enemy_x[0] + 10;
		money_y[0] = enemy_y[0] + 40;
	}
	if (select_money2 == 1)
	{
		money_x[1] = enemy_x[1] + 10;
		money_y[1] = enemy_y[1] + 40;
	}
}

void BackGround::Set_Enemy_Pos(int num)
{
	if (num == 0)
	{
		enemy_x[0] = player_x + 500;
		enemy_y[0] = 200;
	}
	else if (num == 1)
	{
		enemy_x[1] = player_x + 600;
		enemy_y[1] = 200;
	}
}

void BackGround::Set_Front()
{
	if (first_front_created == FALSE)
	{
		Set_Enemy_Pos2(0);
		first_front_created = TRUE;
	}

	if (m_Player_rt.left >= enemy_x_2 + 300)
		first_front_created = FALSE;
}

void BackGround::Set_Enemy_Pos2(int num)
{
	if (num == 0)
	{
		enemy_x_2 = player_x + 700;
		enemy_y_2 = 405;
	}
}

void BackGround::Die_Check()
{
	RECT check;

	for (int i = 0; i < 2; i++)
	{
		if (IntersectRect(&check, &m_Player_rt, &m_Enemy_rt[i]))
		{
			die_check = TRUE;
		}
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
	for (int i = 0; i < 11; i++)
	{
		DeleteObject(m_EnemyBitMap[i]);
		DeleteObject(m_Old_EnemyBitMap[i]);
		DeleteDC(EnemyDC[i]);
	}
}